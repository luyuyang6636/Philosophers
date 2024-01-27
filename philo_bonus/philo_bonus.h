/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luyang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:08:33 by luyang            #+#    #+#             */
/*   Updated: 2024/01/27 18:23:40 by luyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <inttypes.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>

struct	s_philo;

typedef	struct	s_data
{
	struct s_philo	*philos;
	uint64_t	dur_death;
	uint64_t	dur_eat;
	uint64_t	dur_sleep;
	int		n_philo;
	int		eat_goal;
	int		fini;
	uint64_t	start_time;
	sem_t	*fork;
	sem_t	*message;
	sem_t 	*stop;
}	t_data;

typedef struct	s_philo
{
	struct s_data	*data;
	pid_t	pid;
	int		eating;
	uint64_t	time_to_die;
	int	eat_count;
}	t_philo;


int		ft_atoi(char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
uint64_t	get_time(void);
void	ft_usleep(uint64_t time);
void	ft_handle_error(char *error_msg, t_data *data);
void	ft_check_input(char **argv);



#endif
