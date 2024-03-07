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

void	message(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->write);
	if (!philo->data->dead && !ft_strncmp(msg, DEAD_MSG, 5))
	{
		printf("%lu ", (get_time() - philo->data->start_time));
		printf("%d %s\n", philo->id, msg);
		philo->data->dead = 1;
	}
	else if (!philo->data->dead && !ft_strncmp(msg, FINI_MSG, 20))
	{
		printf("%lu ", (get_time() - philo->data->start_time));
		printf("%s\n", msg);
		philo->data->dead = 1;
	}
	if (!philo->data->dead)
	{
		printf("%lu ", (get_time() - philo->data->start_time));
		printf("%d %s\n", philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->write);
}
