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
}



int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;
	
	if (argc != 5 && argv != 6)
		return (1);
	ft_check_input(argv);
	ft_init_data(&data);
	ft_processes(philos);
}
