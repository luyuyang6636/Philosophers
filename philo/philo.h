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

# define DEAD_MSG	"died"
# define EAT_MSG    "is eating"
# define FORK_MSG   "has taken a fork"
# define SLEEP_MSG  "is sleeping"
# define THINK_MSG  "is thinking"

struct	s_data;

typedef struct	s_philo
{
	struct s_data	*data;
	pthread_t	th;
	int		id;
	int		eat_count;
	uint64_t	time_to_die;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	int		eating;
	pthread_mutex_t	lock;
	
}	t_philo;

typedef struct	s_data
{
	pthread_t	*tid;
	t_philo		*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	lock;
	uint64_t	dur_die;
	uint64_t	dur_eat;
	uint64_t	dur_sleep;
	uint64_t	start_time;
	int		n_philo;
	int		eat_goal;
	int		fini;
	int		dead;
}	t_data;

int		ft_handle_error(char *error_msg, t_data *data);
int		ft_check_input(char **argv);
int		ft_init_data(t_data *data, char **argv);
int		ft_init(t_data *data, char **argv);
int		ft_init_array(t_data *data);
int		ft_atoi(char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_thread(t_data *data);
int		ft_strlen(char *s);
u_int64_t	get_time(void);
void	ft_init_forks(t_data *data);
void	ft_init_philos(t_data *data);
void	ft_free_data(t_data *data);
void	ft_exit(t_data *data);
void	message(t_philo *philo, char *msg);
void	ft_usleep(uint64_t time);
void	eat(t_philo *philo);
void	*monitor(void *pdata);
void	*supervisor(void *p);
void	*routine(void *p);


# endif
