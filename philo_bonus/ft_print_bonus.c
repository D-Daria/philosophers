/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrhyhorn <mrhyhorn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:43:42 by mrhyhorn          #+#    #+#             */
/*   Updated: 2022/06/13 14:36:12 by mrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_error_msg(const char *error)
{
	printf("%s%s%s\n", RED, error, BREAK);
	return (ERROR);
}

int	ft_print(t_philo *philo, const char *msg)
{
	t_data	*d;
	long	tm;

	if (!philo->data->is_stop)
	{
		d = philo->data;
		sem_wait(d->print_sem);
		tm = ft_get_time() - philo->data->start_time;
		printf("%ld %d %s\n", tm, philo->philo_num, msg);
		sem_post(d->print_sem);
	}
	return (RTRN_SUCCESS);
}
