/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrhyhorn <mrhyhorn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:29:49 by mrhyhorn          #+#    #+#             */
/*   Updated: 2022/05/26 19:35:16 by mrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_update_eating(t_philo *philo)
{
	pthread_mutex_lock(&(philo->eat_mutex));
	if (philo->done_eating == 0)
		philo->eat_count += 1;
	if (philo->eat_count == philo->data->must_eat)
		philo->done_eating = 1;
	pthread_mutex_unlock(&(philo->eat_mutex));
	return ;
}

int	ft_eating(t_philo *philo)
{
	t_data		*d;

	d = philo->data;
	pthread_mutex_lock(&(d->forks_mutex[philo->l_fork]));
	ft_print(philo, TOOK_FORK);
	if (philo->l_fork == philo->r_fork)
	{
		pthread_mutex_unlock(&(d->forks_mutex[philo->l_fork]));
		usleep(philo->data->time_to_die * 1000);
		return (RTRN_ERROR);
	}
	pthread_mutex_lock(&(d->forks_mutex[philo->r_fork]));
	ft_print(philo, TOOK_FORK);
	ft_print(philo, EATING_MSG);
	pthread_mutex_lock(&(philo->dead_mutex));
	philo->tm_last_eating = ft_get_time('l');
	pthread_mutex_unlock(&(philo->dead_mutex));
	ft_usleep(philo->data, philo->data->time_to_eat);
	ft_update_eating(philo);
	pthread_mutex_unlock(&(d->forks_mutex[philo->r_fork]));
	pthread_mutex_unlock(&(d->forks_mutex[philo->l_fork]));
	return (RTRN_SUCCESS);
}

int	ft_sleeping(t_philo *philo)
{
	ft_print(philo, SLEEP_MSG);
	ft_usleep(philo->data, philo->data->time_to_sleep);
	return (RTRN_SUCCESS);
}

int	ft_thinking(t_philo *philo)
{
	ft_print(philo, THINK_MSG);
	return (RTRN_SUCCESS);
}