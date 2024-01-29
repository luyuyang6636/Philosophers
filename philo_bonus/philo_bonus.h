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
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <unistd.h>


# define  DEAD_MSG	"died"
# define EAT_MSG    "is eating"
# define FORK_MSG   "has taken a fork"
# define SLEEP_MSG  "is sleeping"
# define THINK_MSG  "is thinking"

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
	sem_t	*stop;
	sem_t	*dead;
	sem_t	*change;
}	t_data;

typedef struct	s_philo
{
	struct s_data	*data;
	pid_t	pid;
	int	id;
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
void	ft_clean(t_data *data);
void	message(t_philo *philo, char *msg);
void	eat(t_philo *philo);
void	routine(t_philo *philo);
void	ft_processes(t_data *data);
void	ft_init_data(t_data *data, char **argv);
void	ft_init_philos(t_data *data);
void	*monitor(void *p);
void	*supervisor(void *p);

#endif
