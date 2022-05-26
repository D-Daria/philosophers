/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrhyhorn <mrhyhorn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 22:06:29 by mrhyhorn          #+#    #+#             */
/*   Updated: 2022/05/26 18:16:45 by mrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_init_forks(t_data *data)
{
	int i;
	
	data->forks_mutex = malloc(sizeof(t_mutex) * data->philo_count);
	if (data->forks_mutex == NULL)
		return (RTRN_ERROR);
	i = -1;
	while (++i < data->philo_count)
	{
		if (pthread_mutex_init(&(data->forks_mutex[i]), NULL))
			return (RTRN_ERROR);
	}
	return (RTRN_SUCCESS);
}

int	ft_init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&(data->printf_mutex), NULL))
		return (RTRN_ERROR);
	if (pthread_mutex_init(&(data->all_dead_mutex), NULL))
		return (RTRN_ERROR);
	if (pthread_mutex_init(&(data->all_ate_mutex), NULL))
		return (RTRN_ERROR);
	return (RTRN_SUCCESS);
}

int	ft_init(t_data *data)
{
	int i;
	
	if (ft_init_mutexes(data) == RTRN_ERROR)
		return (RTRN_ERROR);
	if (ft_init_forks(data) == RTRN_ERROR)
		return (RTRN_ERROR);
	data->philo = malloc(sizeof(t_philo) * data->philo_count);
	if (data->philo == NULL)
		return (RTRN_ERROR);
	i = -1;
	while (++i < data->philo_count)
	{
		data->philo[i].philo_num = i + 1;
		data->philo[i].eat_count = 0;
		data->philo[i].done_eating = 0;
		data->philo[i].l_fork = i;
		data->philo[i].r_fork = (i + 1) % data->philo_count;
		if (pthread_mutex_init(&(data->philo[i].dead_mutex), NULL))
			return (RTRN_ERROR);
		if (pthread_mutex_init(&(data->philo[i].eat_mutex), NULL))
			return (RTRN_ERROR);
		data->philo[i].data = data;
	}
	return (RTRN_SUCCESS);
}