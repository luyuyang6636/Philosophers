/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luyang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:11:32 by luyang            #+#    #+#             */
/*   Updated: 2024/01/22 15:12:26 by luyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <inttypes.h>
# include <sys/time.h>



typedef struct	s_data
{
	pthread_t	*tid;
	t_philo		*philos;
	pthread_mutex_t	*forks;
	uint64_t	dur_die;
	uint64_t	dur_eat;
	uint64_t	dur_sleep;
	int		n_philo;
	int		eat_goal;
	int		fini;
}	t_data;

typedef struct	s_philo
{
	t_data	*data;
	pthread_t	th;
	int		id;
	int		eat_count;
	uint64_t	time_to_die;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	int		eating;
	pthread_mutex_t	lock;
	
}	t_philo;

void	ft_handle_error(char *error_msg);
void	ft_check_input(char **argv);
void	ft_init_data(t_data *data, char **argv);
void	ft_init(t_data *data, char **argv);
int		ft_atoi(char *str);

# endif
