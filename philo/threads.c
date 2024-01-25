#include "philo.h"

void	monitor(void *pdata)
{
	t_data	*data;

	data = (t_data *)pdata;

	while (data->dead == 0)
	{
		if (data->fini >= data->n_philo)
			data->dead = 0;
	}
}

void	supervisor(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (!philo->data->dead)
	{
		pthread_mutex_lock(&philo->lock);
		if (get_time() >= philo->time_to_die)
			message(philo, DEAD_MSG);
	}
}

void	routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (pthread_create(&philo->th, NULL, &supervisor, &philo))
		return (ft_handle_error("supervisor thread failed!", philo->data));
	while (philo->data->dead == 0)
	{
		eat(philo);
	}
}

int	ft_thread(t_data *data)
{
	pthread_t	t0;
	int		i;

	i = -1;
	data->start_time = get_time();
	if (data->eat_goal > 0)
	{
		if (pthread_create(&t0, NULL, &monitor, data))
			return (ft_handle_error("monitor thread failed!", data));
	} 
	while (++i < data->n_philo)
	{
		if (pthread_create(&data->tid[i], NULL, &routine, &data->philos[i]))
			return (ft_handle_error("routine thread failed!", data));
	}
	i = -1;

		if (pthread_create(&data->tid[i], NULL, &supervisor, &data->philos[i]))
			return (ft_handle_error("supervisor thread failed!", data));


}
