/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrhyhorn <mrhyhorn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:05:22 by mrhyhorn          #+#    #+#             */
/*   Updated: 2022/05/18 16:02:39 by mrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

/*time in milliseconds*/
// long	ft_get_time_ms(long *current_time)
// {
// 	t_timeval	time;

// 	gettimeofday(&time, NULL);
// 	*current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
// 	return (*current_time);
// }

/*time in microseconds*/
// long	ft_get_time_mcs(void)
// {
// 	t_timeval	time;
// 	long		current_time;

// 	gettimeofday(&time, NULL);
// 	current_time = (time.tv_sec * 1000000) + time.tv_usec;
// 	return (current_time);
// }

long	ft_get_time(char type)
{
	t_timeval	time;
	long		current_time;

	if (type == 'c')
	{
		gettimeofday(&time, NULL);
		current_time = (time.tv_sec * 1000000) + time.tv_usec;
		return (current_time);
	}
	else if (type == 'l')
	{
		gettimeofday(&time, NULL);
		current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
		return (current_time);
	}
	return (0);
}

void	ft_usleep(long time)
{
	long	timestamp;
	
	timestamp = ft_get_time('l');
	while (1)
	{
		if (ft_get_time('l') - timestamp >= time)
			break ;
		usleep(10);
	}
}

void	ft_free(t_data *data)
{
	if (data->philo != NULL)
		free(data->philo);
	if (data->forks != NULL)
		free(data->forks);
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
