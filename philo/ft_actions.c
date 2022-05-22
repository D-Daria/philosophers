/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrhyhorn <mrhyhorn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:29:49 by mrhyhorn          #+#    #+#             */
/*   Updated: 2022/05/22 23:21:11 by mrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_check_max_fork(t_philo *philo, t_forks **max, \
										t_forks **min)
{
	int		left_num;
	int		right_num;

	left_num = philo->left_fork->fork_num;
	right_num = philo->right_fork->fork_num;
	if (left_num == ft_max(left_num, right_num))
	{
		(*max) = philo->left_fork;
		(*min) = philo->right_fork;
		return ;
	}
	else if (right_num == ft_max(left_num, right_num))
	{
		(*max) = philo->right_fork;
		(*min) = philo->left_fork;
		return ;
	}
}

void	ft_update_eating(t_philo *philo)
{
	if (philo->done_eating == 0)
		philo->eat_count += 1;
	if (philo->eat_count == philo->data->must_eat)
		philo->done_eating = 1;
}

int	ft_eating(t_philo *philo)
{
	t_forks		*max_fork;
	t_forks		*min_fork;

	ft_check_max_fork(philo, &max_fork, &min_fork);
	pthread_mutex_lock(&(min_fork->f_mutex));
	ft_print(philo, TOOK_FORK);
	pthread_mutex_lock(&(max_fork->f_mutex));
	ft_print(philo, TOOK_FORK);
	ft_print(philo, EATING_MSG);
	pthread_mutex_lock(&(philo->state_mutex));
	philo->tm_last_eating = ft_get_time('l');
	pthread_mutex_unlock(&(philo->state_mutex));
	ft_usleep(philo->data->time_to_eat);
	// ft_update_eating(philo);
	if (philo->done_eating == 0)
		philo->eat_count += 1;
	if (philo->eat_count == philo->data->must_eat)
		philo->done_eating = 1;
	pthread_mutex_unlock(&(max_fork->f_mutex));
	pthread_mutex_unlock(&(min_fork->f_mutex));
	return (RTRN_SUCCESS);
}

int	ft_sleeping(t_philo *philo)
{
	// pthread_mutex_lock(&(philo->data->all_dead_mutex));
	// if (!philo->data->all_dead)
	// pthread_mutex_unlock(&(philo->data->all_dead_mutex));
	ft_print(philo, SLEEP_MSG);
	ft_usleep(philo->data->time_to_sleep);
	return (RTRN_SUCCESS);
}

int	ft_thinking(t_philo *philo)
{
	// pthread_mutex_lock(&(philo->data->all_dead_mutex));
	// if (!philo->data->all_dead)
	ft_print(philo, THINK_MSG);
	// pthread_mutex_unlock(&(philo->data->all_dead_mutex));
	// ft_print(philo, THINK_MSG);
	return (RTRN_SUCCESS);
}