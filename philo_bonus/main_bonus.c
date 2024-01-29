/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luyang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:06:43 by luyang            #+#    #+#             */
/*   Updated: 2024/01/27 18:24:36 by luyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_check_input(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		if (argv[i][j] && argv[i][j] == ' ')
			j++;
		if (argv[i][j] == '-')
			ft_handle_error("Negative input", NULL);
		while (argv[i][j])
		{
			if (argv[i][j] < 48 || argv[i][j] > 57)
				ft_handle_error("Input are not all integers", NULL);
			j++;
		}
		i++;
	}
}

void	ft_handle_error(char *error_msg, t_data *data)
{
	printf("Error: %s\n", error_msg);
	if (data)
		ft_clean(data);
	exit(EXIT_FAILURE);
}

void	ft_clean(t_data *data)
{
	int	i;
	
	i = -1;
	if (data->philos)
	{
		while (++i < data->n_philo)
		{
			if (data->philos[i].pid == 0)
				kill(data->philos[i].pid, SIGKILL);
		}
		free (data->philos);
	}
	sem_close(data->fork);
	sem_close(data->change);
	sem_close(data->stop);
	sem_close(data->message);
	sem_close(data->dead);
}

int	main(int argc, char **argv)
{
	t_data	data;
	
	if (argc != 5 && argc != 6)
		return (1);
	ft_check_input(argv);
	ft_init_data(&data, argv);
	ft_init_philos(&data);
	sem_wait(data.stop);
	ft_processes(&data);
	sem_wait(data.stop);
	ft_clean(&data);
	return (0);
}
