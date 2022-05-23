/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_destroy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrhyhorn <mrhyhorn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 19:42:03 by mrhyhorn          #+#    #+#             */
/*   Updated: 2022/05/23 22:44:33 by mrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_join_threads(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->philo_count)
	{
		if (pthread_join(data->philo[i].thread, NULL))
			return (RTRN_ERROR);
	}
	// if (pthread_join(data->check_death_th, NULL))
	// 	return (RTRN_ERROR);
	return (RTRN_SUCCESS);
}

int	ft_delete_forks(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->philo_count)
	{
		if (pthread_mutex_destroy(&(data->forks[i].f_mutex)))
			return (RTRN_ERROR);
	}
	return (RTRN_ERROR);
}

int	ft_destroy_mutexes(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->philo_count)
	{
		if (pthread_mutex_destroy(&(data->forks[i].f_mutex)))
			return (RTRN_ERROR);
		if (pthread_mutex_destroy(&(data->philo[i].dead_mutex)))
			return (RTRN_ERROR);
		if (pthread_mutex_destroy(&(data->philo[i].eat_mutex)))
			return (RTRN_ERROR);
	}
	if (pthread_mutex_destroy(&(data->all_dead_mutex)))
		return (RTRN_ERROR);
	if (pthread_mutex_destroy(&(data->all_ate_mutex)))
		return (RTRN_ERROR);
	if (pthread_mutex_destroy(&(data->printf_mutex)))
		return (RTRN_ERROR);
	return (RTRN_SUCCESS);
}

int	ft_join_destroy(t_data *data)
{
	if (ft_join_threads(data) == RTRN_ERROR)
		return (RTRN_ERROR);
	if (ft_destroy_mutexes(data) == RTRN_ERROR)
		return (RTRN_ERROR);
	return (RTRN_SUCCESS);
}