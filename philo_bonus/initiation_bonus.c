/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luyang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:32:26 by luyang            #+#    #+#             */
/*   Updated: 2024/01/27 18:34:27 by luyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_init_data(t_data *data, char **argv)
{
	data->n_philo = ft_atoi(argv[1]);
	data->dur_death = ft_atoi(argv[2]);
	data->dur_eat = ft_atoi(argv[3]);
	data->dur_sleep = ft_atoi(argv[4]);
	data->start_time = get_time();
	if (argv[5])
		data->eat_goal = ft_atoi(argv[5]);
	else
		data->eat_goal = -1;
	data->fini = 0;
	sem_unlink("fork");
	sem_unlink("message");
	sem_unlink("stop");
	sem_unlink("dead");
	sem_unlink("change");
	data->fork = sem_open("fork", O_CREAT, 0600, data->n_philo);
	data->change = sem_open("change", O_CREAT, 0600, 0);
	data->message = sem_open("message", O_CREAT, 0600, 1);
	data->stop = sem_open("stop", O_CREAT, 0600, 1);
	data->dead = sem_open("dead", O_CREAT, 0600, 1);
}

void	ft_init_philos(t_data *data)
{
	int	i;

	i = -1;
	data->philos = malloc (sizeof(t_philo) * data->n_philo);
	if (!data->philos)
		ft_handle_error("malloc failed!", data);
	while (++i < data->n_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eating = 0;
		data->philos[i].time_to_die = get_time() + data->dur_death;
		data->philos[i].eat_count = 0;
		data->philos[i].data = data;
	}
}
