#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	pthread_mutex_lock(&philo->r_fork);
	message(philo, FORK_MSG);
	pthread_mutex_lock(&philo->l_fork);
	message(philo, FORK_MSG);
	message(philo, EAT_MSG);
	philo->time_to_die = get_time() + philo->data->dur_die;
	philo->eating = 1;
	philo->eat_count++;
	ft_usleep(philo->data->dur_eat);
	pthread_mutex_unlock(&philo->r_fork);
	pthread_mutex_unlock(&philo->l_fork);
	message(philo, SLEEP_MSG);
	ft_usleep(philo->data
}

void	message(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->write);
	if (!philo->data->dead)
	{
		printf("%llu ", (get_time() - philo->data->start_time));
		printf("%d %s", philo->id, msg);
		if (!ft_strncmp(msg, DEAD_MSG, 9));
			philo->data->dead = 1;
	}	
	pthread_mutex_unlock(&philo->data->write);
}
