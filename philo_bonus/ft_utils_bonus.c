/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrhyhorn <mrhyhorn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:36:30 by mrhyhorn          #+#    #+#             */
/*   Updated: 2022/06/13 18:44:24 by mrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_close_sems(t_data *data)
{
	int		i;

	sem_close(data->dead_sem);
	sem_close(data->control_sem);
	sem_close(data->all_ate_sem);
	sem_close(data->print_sem);
	sem_close(data->forks_sem);
	i = -1;
	while (++i < data->philo_count)
		sem_close(data->philo[i].philo_sem);
}

long	ft_get_time(void)
{
	t_timeval	time;
	long		current_time;

	gettimeofday(&time, NULL);
	current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (current_time);
}

void	ft_usleep(long time)
{
	long	timestamp;

	timestamp = ft_get_time();
	while (1)
	{
		if (ft_get_time() - timestamp >= time)
			break ;
		usleep(100);
	}
}

long	ft_atol(const char *str)
{
	int		i;
	long	result;
	int		sign;

	result = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\r'
		|| str[i] == '\f'
		|| str[i] == '\v'
		|| str[i] == '\n')
		i++;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}
