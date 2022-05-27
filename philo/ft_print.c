/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrhyhorn <mrhyhorn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:43:42 by mrhyhorn          #+#    #+#             */
/*   Updated: 2022/05/26 22:03:04 by mrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error_msg(const char *error)
{
	printf("%s%s%s\n", RED, error, BREAK);
	return (RTRN_ERROR);
}

int	ft_print(t_philo *philo, const char *msg)
{
	long	tm;

	tm = ft_get_time('l') - philo->data->start_time;
	if (!ft_is_stop(philo->data, 'd'))
	{
		pthread_mutex_lock(&(philo->data->printf_mutex));
		printf("%ld %d %s\n", tm, philo->philo_num, msg);
		pthread_mutex_unlock(&(philo->data->printf_mutex));
	}
	return (RTRN_SUCCESS);
}
