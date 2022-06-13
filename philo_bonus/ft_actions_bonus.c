/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrhyhorn <mrhyhorn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:00:15 by mrhyhorn          #+#    #+#             */
/*   Updated: 2022/06/13 18:23:33 by mrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*ft_eat_exit(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	sem_wait(philo->data->control_sem);
	sem_post(philo->data->dead_sem);
	exit(ALL_ATE);
}

void	ft_update_eating(t_philo *philo)
{
	pthread_t	th;

	if (pthread_create(&th, NULL, &ft_eat_exit, philo))
	{
		sem_post(philo->data->dead_sem);
		exit(EXIT_FAILURE);
	}
	pthread_detach(th);
	if (philo->done_eating == 0)
		philo->eat_count += 1;
	if (philo->eat_count == philo->data->must_eat)
	{
		philo->done_eating = 1;
		sem_post(philo->data->all_ate_sem);
	}
}

int	ft_eating(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	sem_wait(data->forks_sem);
	ft_print(philo, TOOK_FORK);
	sem_wait(data->forks_sem);
	ft_print(philo, TOOK_FORK);
	ft_print(philo, EATING_MSG);
	// gettimeofday(&philo->last_eat, 0);
	sem_wait(philo->philo_sem);
	philo->tm_last_eating = ft_get_time();
	sem_post(philo->philo_sem);
	ft_usleep(philo->data->time_to_eat);
	if (philo->data->must_eat > 0)
		ft_update_eating(philo);
	sem_post(data->forks_sem);
	sem_post(data->forks_sem);
	return (RTRN_SUCCESS);
}

int	ft_sleeping(t_philo *philo)
{
	ft_print(philo, SLEEP_MSG);
	ft_usleep(philo->data->time_to_sleep);
	return (RTRN_SUCCESS);
}

int	ft_thinking(t_philo *philo)
{
	ft_print(philo, THINK_MSG);
	return (RTRN_SUCCESS);
}
