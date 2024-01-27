/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luyang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:26:15 by luyang            #+#    #+#             */
/*   Updated: 2024/01/27 18:27:00 by luyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(char *str)
{
	uint64_t	n;

	n = 0;
	while (*str == ' ')
		str++;
	while (*str >= 48 && *str <= 57)
	{
		n = n * 10 + *str - 48;
		str++;
	}
	return (n);
}

uint64_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		ft_handle_error("Failure to get time of day!", NULL);
	return (time.tv_sec * (uint64_t)1000 + time.tv_usec / 1000);
}

void	ft_usleep(uint64_t time)
{
	uint64_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!s1 || !s2)
		return (1);
	if (n == 0)
		return (0);
	while (--n && *s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
