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

#include <philo_bonus.h>

void	ft_init_data(t_data *data, char **argv)
{
	data->n_philo = ft_atoi(argv[1]);
	data->dur_death = ft_atoi(argv[2]);
	data->dur_eat = ft_atoi(argv[3]);
	data->dur_sleep = ft_atoi(argv[4]);
	data->start_time = get_time();
	data->fini = 0;
	if (argv[5])
		data->eat_goal = ft_atoi(argv[5]);
	else
		data->eat_goal = -1;
	sem_unlink("fork");
	sem_unlink("message");
	sem_unlink("stop");
	data->fork = sem_open("fork", O_CREAT, 0600, n_philo);
	data->message = sem_open("message", O_CREAT, 0600, 0);
	data->stop = sem_open("stop", O_CREAT, 0600, 1);
}
	

