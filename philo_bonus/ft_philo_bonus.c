/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrhyhorn <mrhyhorn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:45:10 by mrhyhorn          #+#    #+#             */
/*   Updated: 2022/06/13 14:52:03 by mrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_wait_exit(t_data *data)
{
	int	i;
	int	status;

	waitpid(-1, &status, 0);
	if (WEXITSTATUS(status) == ALL_DEAD)
	{
		i = -1;
		while (++i < data->philo_count)
		{
			sem_post(data->all_ate_sem);
			kill(data->philo[i].pid, SIGKILL);
		}
		return (RTRN_SUCCESS);
	}
	else if (WEXITSTATUS(status) == EXIT_FAILURE)
		return (ft_error_msg("Error in process\n"));
	i = -1;
	while (++i < data->philo_count)
		kill(data->philo[i].pid, SIGKILL);
	return (RTRN_SUCCESS);
}

void	*ft_stop(void *arg)
{
	t_philo		*philo;
	long		tm;
	t_timeval	time;

	philo = (t_philo *)arg;
	usleep(1000);
	while (1)
	{
		gettimeofday(&time, 0);
		tm = (time.tv_sec * 1000) + (time.tv_usec / 1000);
		if (tm - ((philo->last_eat.tv_sec * 1000) \
					+ (philo->last_eat.tv_usec / 1000)) \
					>= philo->data->time_to_die)
		{
			sem_wait(philo->data->print_sem);
			tm = ft_get_time() - philo->data->start_time;
			printf("%ld %d %s\n", tm, philo->philo_num, DIED_MSG);
			sem_post(philo->data->dead_sem);
			exit(ALL_DEAD);
		}
		usleep(100);
	}
	return (NULL);
}

void	ft_process(t_philo *philo)
{
	pthread_t	th;
	t_data		*data;

	data = philo->data;
	gettimeofday(&philo->last_eat, 0);
	if (pthread_create(&th, NULL, &ft_stop, philo))
	{
		sem_post(philo->data->dead_sem);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		ft_eating(philo);
		ft_sleeping(philo);
		ft_thinking(philo);
	}
	pthread_join(th, NULL);
	exit(EXIT_SUCCESS);
}

void	*ft_all_ate(void *arg)
{
	t_data	*data;
	int		count;

	data = (t_data *)arg;
	count = 0;
	while (1)
	{
		sem_wait(data->all_ate_sem);
		count += 1;
		if (count == data->philo_count)
		{
			sem_post(data->control_sem);
			return (NULL);
		}
	}
	return (NULL);
}

int	ft_philo(t_data *data)
{
	pthread_t	eating_th;
	int			i;

	data->all_dead = 0;
	data->all_have_eaten = 0;
	data->start_time = ft_get_time();
	i = -1;
	while (++i < data->philo_count)
	{
		data->philo[i].pid = fork();
		if (data->philo[i].pid < 0)
			return (ERROR);
		else if (data->philo[i].pid == 0)
			ft_process(&data->philo[i]);
	}
	if (data->must_eat > 0)
	{
		if (pthread_create(&eating_th, NULL, &ft_all_ate, data))
			return(ERROR);
		pthread_detach(eating_th);
	}
	sem_wait(data->dead_sem);
	ft_wait_exit(data);
	ft_close_sems(data);
	return (RTRN_SUCCESS);
}
