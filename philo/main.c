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

	i = 1;
	while (argv[i])
	{
		while (*argv[i] && *argv[i] == ' ')
			argv[i]++;
		while (*argv[i])
		{
			if (*argv[i] < 48 || *argv[i] > 57)
				return (ft_handle_error("Input are not all integers", NULL));
			argv[i]++;
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
	ft_free_data(&data);
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

	if (argc == 4 || argc == 5)
	{
		if (ft_check_input(argv))
			return (1);
		if (ft_init(&data, argv))
			return (1);
		if (ft_thread(&data))
			return (1);
	}
	return (0);
}
