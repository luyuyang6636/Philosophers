/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luyang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:56:51 by luyang            #+#    #+#             */
/*   Updated: 2024/01/22 15:57:41 by luyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_array(t_data *data)
{
	data->tid = malloc(sizeof(pthread_t) * data->n_philo);
	if (!data->tid)
		return (ft_handle_error ("thread malloc failed!", data));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->forks)
		return (ft_handle_error("forks malloc failed!", data));
	data->philos = malloc(sizeof(t_philo) * data->n_philo);
	if (!data->philos)
		return (ft_handle_error("t_philo malloc failed!", data));
	return (0);
}

void	ft_init_forks(t_data *data)
{
	int	i;
	
	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		if(i != 0)
		{
			data->philos[i].r_fork = &data->forks[i];
			data->philos[i].l_fork = &data->forks[i - 1];
		}
		i++;
	}
	data->philos[0].r_fork = &data->forks[0];
	data->philos[0].l_fork = &data->forks[data->n_philo - 1];
}

int	ft_init_data(t_data *data, char **argv)
{
	data->n_philo = ft_atoi(argv[1]);
	data->dur_die = ft_atoi(argv[2]);
	data->dur_eat = ft_atoi(argv[3]);
	data->dur_sleep = ft_atoi(argv[4]);
	if (*argv[5])
		data->eat_goal = ft_atoi(argv[5]);
	else
		data->eat_goal = -1;
	if (data->n_philo < 1 || data->dur_die < 0 || data->dur_eat < 0
		|| data->dur_sleep < 0)
		return (1);
	data->fini = 0;
	data->dead = 0;
	pthread_mutex_init(&data->lock, NULL);
	pthread_mutex_init(&data->write, NULL);
	return (0);
}

void	ft_init_philos(t_data *data)
{
	int	i;
	
	i = 0;
	while (i < data->n_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].time_to_die = data->dur_die;
		data->philos[i].eat_count = 0;
		data->philos[i].eating = 0;
		pthread_mutex_init(&data->philos[i].lock, NULL);
        i++;
    }
}
	
	

int	ft_init(t_data *data, char **argv)
{
	if (ft_init_data(data, argv))
		return (1);
	if (ft_init_array(data))
		return (1);
	ft_init_forks(data);
	ft_init_philos(data);
	return (0);
}
