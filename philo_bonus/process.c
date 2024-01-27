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

void	*supervisor(t_philo *philo)
{
	
}


void	routine(t_philo *philo)
{
	pthread_t	t0;

	if (pthread_create(&t0, NULL, &supervisor, philo))
		ft_handle_error("pthread_create error!", );
	sem_wait(philo->data->stop);
	
}

void	ft_processes(t_data *data, t_philo *philos)
{
	int	i;
	
	i = 0;
	philos = malloc(sizeof(t_philo) * data->n_philo);
	if (!philos)
		ft_handle_error("philos malloc error!", )
	while (i < data->n_philo)
	{
		philos[i].pid = fork();
		if (philos[i].pid == 0)
			routine(&philos[i]);
	}
}
