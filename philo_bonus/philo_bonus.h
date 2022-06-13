/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrhyhorn <mrhyhorn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:30:52 by mrhyhorn          #+#    #+#             */
/*   Updated: 2022/06/13 19:17:39 by mrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h> /* O_CREATE | O_EXCL */

/*---EXITS---*/
# define ERROR			1
# define RTRN_SUCCESS	0

/*---COLORS---*/
# define RED		"\033[0;31m"
# define BREAK		"\033[0m"

/*---MSGS---*/
# define TOOK_FORK	"has taken a fork"
# define EATING_MSG	"is eating"
# define SLEEP_MSG	"is sleeping"
# define THINK_MSG	"is thinking"
# define DIED_MSG	"died"

/*---SEMAPHORES---*/
# define PRINT_SEM_NAME		"/printSem"
# define DEAD_SEM_NAME		"/allDeadSem"
# define ALL_ATE_SEM_NAME	"/allAteSem"	
# define CTRL_SEM_NAME		"/controlSem"
# define FORKS_SEM_NAME		"/forkSem"

# define ALL_DEAD	2
# define ALL_ATE	3

/*---SYSTEM_STRUCTS---*/
typedef struct timeval	t_timeval;

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

typedef struct s_philo {
	int			philo_num;
	int			eat_count;
	int			done_eating;
	int			is_dead;
	int			done;
	long		tm_last_eating;
	sem_t		*philo_sem;
	pid_t		pid;
	t_data		*data;
}				t_philo;

typedef struct s_data {
	sem_t		*all_ate_sem;
	sem_t		*dead_sem;
	sem_t		*control_sem;
	sem_t		*forks_sem;
	sem_t		*print_sem;
	int			is_stop;
	int			all_dead;
	int			all_have_eaten;
	long		start_time;
	int			philo_count;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	int			must_eat;
	t_philo		*philo;
}				t_data;

/*ft_utils_bonus.c*/
long	ft_atol(const char *str);
long	ft_get_time(void);
void	ft_usleep(long time);
void	ft_close_sems(t_data *data);

/*ft_parse_input_bonus.c*/
int		ft_parse_input(int argc, char **argv, t_data *data);

/*ft_init_bonus.c*/
int		ft_init(t_data *data);

/*ft_philo_bonus.c*/
int		ft_philo(t_data *data);

/*ft_actions_bonus.c*/
void	ft_update_eating(t_philo *philo);
int		ft_eating(t_philo *philo);
int		ft_sleeping(t_philo *philo);
int		ft_thinking(t_philo *philo);

/*ft_print_bonus.c*/
int		ft_error_msg(const char *error);
int		ft_print(t_philo *philo, const char *msg);

/*ft_itoa.c*/
char	*ft_itoa(int n);

#endif