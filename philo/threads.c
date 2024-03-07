/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luyang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:59:41 by luyang            #+#    #+#             */
/*   Updated: 2024/01/31 16:59:43 by luyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *pdata)
{
	t_data	*data;

	data = (t_data *)pdata;
	while (data->dead == 0)
	{
		pthread_mutex_lock(&data->lock);
		if (data->fini >= data->n_philo)
			message(&data->philos[0], FINI_MSG);
		pthread_mutex_unlock(&data->lock);
	}
	return ((void *)0);
}

void	*supervisor(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (get_time() >= philo->time_to_die && !philo->eating)
			message(philo, DEAD_MSG);
		if (philo->eat_count == philo->data->eat_goal)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->data->fini++;
			philo->eat_count++;
			pthread_mutex_unlock(&philo->data->lock);
		}
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	message(philo, FORK_MSG);
	pthread_mutex_lock(philo->r_fork);
	message(philo, FORK_MSG);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	message(philo, EAT_MSG);
	philo->time_to_die = get_time() + philo->data->dur_die;
	philo->eat_count++;
	ft_usleep(philo->data->dur_eat);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	if (!philo->data->dead)
	{
		message(philo, SLEEP_MSG);
		ft_usleep(philo->data->dur_sleep);
	}
}

void	*routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	philo->time_to_die = philo->data->dur_die + get_time();
	if (pthread_create(&philo->th, NULL, &supervisor, philo))
		return ((void *)1);
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
	int			i;

	i = -1;
	if (data->eat_goal > 0)
	{
		if (pthread_create(&t0, NULL, &monitor, data))
			return (ft_handle_error("monitor thread failed!", data));
	}
	while (++i < data->n_philo)
	{
		if (pthread_create(&data->tid[i], NULL, &routine, &data->philos[i]))
			return (ft_handle_error("routine thread failed!", data));
		ft_usleep(1);
	}
	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_join(data->tid[i], NULL))
			return (ft_handle_error("pthread_join failed!", data));
	}
	return (0);
}
