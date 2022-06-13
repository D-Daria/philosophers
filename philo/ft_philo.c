/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrhyhorn <mrhyhorn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 12:31:20 by mrhyhorn          #+#    #+#             */
/*   Updated: 2022/06/13 19:13:35 by mrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_stop(t_data *data, int type)
{
	if (type == 'd')
	{
		pthread_mutex_lock(&(data->all_dead_mutex));
		if (data->all_dead)
		{
			pthread_mutex_unlock(&(data->all_dead_mutex));
			return (1);
		}
		pthread_mutex_unlock(&(data->all_dead_mutex));
		return (0);
	}
	if (type == 'e')
	{
		pthread_mutex_lock(&(data->all_ate_mutex));
		if (data->all_have_eaten)
		{
			pthread_mutex_unlock(&(data->all_ate_mutex));
			return (1);
		}
		pthread_mutex_unlock(&(data->all_ate_mutex));
	}
	return (0);
}

int	ft_eat_count(t_philo *ph)
{
	static int	c;

	pthread_mutex_lock(&(ph->eat_mutex));
	if (ph->done_eating == 1)
	{
		c += 1;
		ph->done_eating = -1;
	}
	pthread_mutex_unlock(&(ph->eat_mutex));
	if (c == ph->data->philo_count)
	{
		pthread_mutex_lock(&(ph->data->all_ate_mutex));
		ph->data->all_have_eaten = 1;
		pthread_mutex_unlock(&(ph->data->all_ate_mutex));
		return (1);
	}
	return (0);
}

void	*ft_stop_data(void *arg)
{
	t_data	*d;
	int		i;

	d = (t_data *)arg;
	while (!d->all_dead && !d->all_have_eaten)
	{
		i = -1;
		while (++i < d->philo_count)
		{
			ft_eat_count(&d->philo[i]);
			pthread_mutex_lock(&(d->philo[i].dead_mutex));
			if (ft_get_time('l') - d->philo[i].tm_last_eating >= d->time_to_die)
			{
				ft_print(&(d->philo[i]), DIED_MSG);
				pthread_mutex_lock(&(d->all_dead_mutex));
				d->all_dead = 1;
				pthread_mutex_unlock(&(d->all_dead_mutex));
			}
			pthread_mutex_unlock(&(d->philo[i].dead_mutex));
		}
		usleep(100);
	}
	return (NULL);
}

void	*ft_act(void *arg)
{
	t_philo		*philo;
	t_data		*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->philo_num % 2 == 0)
		usleep(100);
	while (!ft_is_stop(data, 'd'))
	{
		ft_eating(philo);
		if (ft_is_stop(data, 'e'))
			break ;
		ft_sleeping(philo);
		ft_thinking(philo);
	}
	return (NULL);
}

int	ft_philo(t_data *data)
{
	t_philo		*ph;
	int			i;

	ph = data->philo;
	data->all_have_eaten = 0;
	data->all_dead = 0;
	data->start_time = ft_get_time('l');
	i = -1;
	while (++i < data->philo_count)
	{
		ph[i].tm_last_eating = ft_get_time('l');
		if (pthread_create(&(ph[i].thread), NULL, &ft_act, &(ph[i])))
			return (RTRN_ERROR);
	}
	if (pthread_create(&data->stop_th, NULL, &ft_stop_data, data))
		return (RTRN_ERROR);
	ft_join_destroy(data);
	return (RTRN_SUCCESS);
}
