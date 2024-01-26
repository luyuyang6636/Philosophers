#include "philo.h"

void	*monitor(void *pdata)
{
	t_data	*data;

	data = (t_data *)pdata;

	while (data->dead == 0)
	{
		if (data->fini >= data->n_philo)
			data->dead = 1;
	}
	return ((void *)0);
}

void	*supervisor(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (!philo->data->dead)
	{
		pthread_mutex_lock(&philo->lock);
		if (get_time() >= philo->time_to_die && !philo->eating)
			message(philo, DEAD_MSG);
		if (philo->eat_count == philo->data->eat_goal)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->data->fini++;
			pthread_mutex_unlock(&philo->data->lock);
			philo->eat_count++;
		}
		
	}
	return ((void *)0);
}

void	*routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (pthread_create(&philo->th, NULL, &supervisor, &philo))
	{
		ft_handle_error("supervisor thread failed!", philo->data);
		return ((void *)1);
	}
	while (philo->data->dead == 0)
	{
		eat(philo);
		message(philo, THINK_MSG);
	}
	if (pthread_join(philo->th, NULL))
		return ((void *)1);
	return (NULL);
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
	while (++i < data->n_philo)
	{
		if (pthread_join(data->tid[i], NULL))
			return (1);
	}
	return (0);



}
