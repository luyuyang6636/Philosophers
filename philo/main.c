/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luyang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:44:14 by luyang            #+#    #+#             */
/*   Updated: 2024/01/22 15:44:47 by luyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_input(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		if (argv[i][j] && argv[i][j] == ' ')
			j++;
		while (argv[i][j])
		{
			if (argv[i][j] < 48 || argv[i][j] > 57)
				return (ft_handle_error("Input are not all integers", NULL));
			j++;
		}
		i++;
	}
	return (0);
}

void	ft_free_data(t_data *data)
{
	if (data->tid)
		free(data->tid);
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
}

void	ft_exit(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].lock);
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->lock);
	ft_free_data(data);
}

int	ft_handle_error(char *error_msg, t_data *data)
{
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
	write(STDERR_FILENO, "\n", 1);
	if (data)
		ft_exit(data);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (1);
	if (ft_check_input(argv))
		return (1);
	if (ft_init(&data, argv))
		return (1);
	if (data.n_philo == 1)
	{
		message(&data.philos[0], FORK_MSG);
		ft_usleep(data.dur_sleep);
		message(&data.philos[0], DEAD_MSG);
	}
	if (ft_thread(&data))
		return (1);
	ft_exit(&data);
	return (0);
}
