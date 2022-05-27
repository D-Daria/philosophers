/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrhyhorn <mrhyhorn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:54:37 by mrhyhorn          #+#    #+#             */
/*   Updated: 2022/05/27 17:27:16 by mrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

/*---EXITS---*/
# define RTRN_ERROR		1
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

/*---SYSTEM_STRUCTS---*/
typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_timeval;

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

typedef struct s_philo {
	int			philo_num;
	int			eat_count;
	int			done_eating;
	long		tm_last_eating;
	t_mutex		dead_mutex;
	t_mutex		eat_mutex;
	pthread_t	thread;
	int			l_fork;
	int			r_fork;
	t_data		*data;
}				t_philo;

typedef struct s_data {
	t_mutex		printf_mutex;
	t_mutex		all_dead_mutex;
	t_mutex		all_ate_mutex;
	t_mutex		*forks_mutex;
	pthread_t	stop_th;
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

/*ft_utils.c*/
void	ft_free(t_data *data);
long	ft_get_time(char type);
void	ft_usleep(t_data *data, long time);
long	ft_atol(const char *str);

/*ft_parse_input.c*/
int		ft_parse_input(int argc, char **argv, t_data *data);

/*ft_init.c*/
int		ft_init(t_data *data);

/*ft_philo.c*/
void	*ft_philo_act(void *arg);
int		ft_philo(t_data *data);

/*ft_stop.c*/
void	*ft_stop_data(void *arg);
int		ft_is_stop(t_data *data, int type);

/*ft_print.c*/
int		ft_print(t_philo *philo, const char *msg);
int		ft_error_msg(const char *error);

/*ft_actions.c*/
int		ft_eating(t_philo *philo);
int		ft_sleeping(t_philo *philo);
int		ft_thinking(t_philo *philo);

/*ft_join_destroy.c*/
int		ft_join_destroy(t_data *data);
int		ft_join_threads(t_data *data);
int		ft_destroy_mutexes(t_data *data);

#endif