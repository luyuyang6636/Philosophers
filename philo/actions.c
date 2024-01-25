#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	pthread_mutex_lock(&philo->r_fork);
	pthread_mutex_lock(&philo->l_fork);
	ft_usleep(philo->data->dur_eat);
	pthread_mutex_unlock(&philo->r_fork);
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
