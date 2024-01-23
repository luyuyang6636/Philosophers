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

void	ft_check_input(char **argv)
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
				ft_handle_error("Input are not all integers");
			argv[i]++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 4 || argc == 5)
	{
		ft_check_input(argv);
		ft_init(&data, argv);        
	}
    
}
