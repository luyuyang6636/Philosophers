/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luyang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 19:11:17 by luyang            #+#    #+#             */
/*   Updated: 2024/01/27 19:12:47 by luyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor(void *p)
{
	t_data	*data;

	data = (t_data *)p;
	while (1)
	{
		sem_wait(data->change);
		data->fini++;
		if (data->fini >= data->n_philo)
		{
			message(&data->philos[0], FINI_MSG);
			sem_post(data->stop);
			break ;
		}
	}
	return (NULL);
}

void	eat(t_philo *philo)
{
	sem_wait(philo->data->fork);
	message(philo, FORK_MSG);
	sem_wait(philo->data->fork);
	message(philo, FORK_MSG);
	philo->eating = 1;
	philo->eat_count++;
	philo->time_to_die = get_time() + philo->data->dur_death;
	message(philo, EAT_MSG);
	ft_usleep(philo->data->dur_eat);
	philo->eating = 0;
	sem_post(philo->data->fork);
	sem_post(philo->data->fork);
	message(philo, SLEEP_MSG);
	ft_usleep(philo->data->dur_sleep);
}

void	*supervisor(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (1)
	{
		if (get_time() >= philo->time_to_die && philo->eating == 0)
		{
			sem_wait(philo->data->dead);
			message(philo, DEAD_MSG);
			sem_post(philo->data->stop);
			break ;
		}
		if (philo->data->eat_goal != -1
			&& philo->eat_count == philo->data->eat_goal)
		{
			sem_post(philo->data->change);
			philo->eat_count++;
		}
	}
	return (NULL);
}

void	routine(t_philo *philo)
{
	pthread_t	t0;

	if (pthread_create(&t0, NULL, &supervisor, philo))
		ft_handle_error("pthread_create error!", philo->data);
	if (pthread_detach(t0))
		ft_handle_error("pthread_detach error!", philo->data);
	while (1)
	{
		eat(philo);
		message(philo, THINK_MSG);
		usleep (200);
	}
}

void	ft_processes(t_data *data)
{
	int			i;
	pthread_t	mon;

	i = -1;
	if (data->eat_goal > 0)
	{
		if (pthread_create(&mon, NULL, &monitor, data))
			ft_handle_error("pthread_create error!", data);
	}
	while (++i < data->n_philo)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == 0)
		{
			routine(&data->philos[i]);
		}
		usleep(100);
	}
}
