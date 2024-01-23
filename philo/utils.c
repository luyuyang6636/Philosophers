/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luyang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:39:14 by luyang            #+#    #+#             */
/*   Updated: 2024/01/22 15:39:41 by luyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_handle_error(char *error_msg)
{
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

int	ft_atoi(char *str)
{
	uint64_t	n;
	
	n = 0;
	while (*str == ' ')
		str++;
	while (*str >= 48 && *str <= 57)
	{
		n = n * 10 + *str;
		str++;
	}
	return (n);
}
