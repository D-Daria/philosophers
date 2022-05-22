/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrhyhorn <mrhyhorn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 12:31:20 by mrhyhorn          #+#    #+#             */
/*   Updated: 2022/05/22 23:15:19 by mrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_set_all_dead(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->philo_count)
	{
		pthread_mutex_lock(&(data->philo[i].is_dead_mutex));
		data->philo[i].is_dead = DEAD;
		pthread_mutex_unlock(&(data->philo[i].is_dead_mutex));
	}
}
/*
void	*ft_stop(void *arg)
{
	t_data	*data;
	t_philo	*philo;
	int		i;

	data = (t_data *)arg;
	philo = data->philo;
	while (1)
	{
		i = -1;
		while (++i < data->philo_count)
		{
			pthread_mutex_lock(&(philo[i].state_mutex));
			if (ft_get_time('l') - philo[i].tm_last_eating > data->time_to_die)
			{
				ft_print(&(philo[i]), DIED_MSG);
				pthread_mutex_unlock(&(philo[i].state_mutex));
				ft_set_all_dead(data);
				pthread_mutex_lock(&(data->philo[i].is_dead_mutex));
				return (NULL);
			}
			pthread_mutex_unlock(&(philo[i].state_mutex));
		}
	}
	return (NULL);
}

void	*ft_act(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_num % 2 == 0)
		usleep(100);
	while (1)
	{
		if (philo->is_dead == DEAD)
			break ;
		ft_eating(philo);
		if (philo->is_dead == DEAD)
			break ;
		ft_sleeping(philo);
		if (philo->is_dead == DEAD)
			break ;
		ft_thinking(philo);
	}
	pthread_mutex_unlock(&(philo->is_dead_mutex));
	return (NULL);
}
*/

void	*ft_stop(void *arg)
{
	t_data	*data;
	t_philo	*ph;

	ph = (t_philo *)arg;
	data = ph->data;
	// pthread_mutex_lock(&(data->check_mutex));
	while (1)
	{
		pthread_mutex_lock(&(ph->state_mutex));
		if (ft_get_time('l') - ph->tm_last_eating > data->time_to_die)
		{
			pthread_mutex_unlock(&(ph->state_mutex));
			ft_print(ph, DIED_MSG);
			pthread_mutex_lock(&(data->all_dead_mutex));
			data->all_dead = 1;
			pthread_mutex_unlock(&(data->all_dead_mutex));
			break ;
		}
		pthread_mutex_unlock(&(ph->state_mutex));
		usleep(100);
	}
	// pthread_mutex_unlock(&(data->check_mutex));
	return (NULL);
}

void	*ft_act(void *arg)
{
	pthread_t	stop_th;
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->philo_num % 2 == 0)
		usleep(100);
	if (pthread_create(&stop_th, NULL, ft_stop, philo))
		return (NULL);
	while (1)
	{
		pthread_mutex_lock(&(philo->data->all_dead_mutex));
		if (philo->data->all_dead)
		{
			pthread_mutex_unlock(&(philo->data->all_dead_mutex));
			break ;
		}
		pthread_mutex_unlock(&(philo->data->all_dead_mutex));
		ft_eating(philo);
		ft_sleeping(philo);
		ft_thinking(philo);
	}
	pthread_detach(stop_th);
	// pthread_mutex_unlock(&(philo->data->all_dead_mutex));
	// pthread_mutex_unlock(&(philo->data->check_mutex));
	return (NULL);
}

int	ft_philo(t_data *data)
{
	// pthread_t	check_th;
	t_philo		*ph;
	int			i;

	ph = data->philo;
	data->start_time = ft_get_time('l');
	data->all_done_eating = 0;
	data->all_dead = 0;
	i = -1;
	while (++i < data->philo_count)
	{
		ph[i].tm_last_eating = data->start_time;
		if (pthread_create(&(ph[i].thread), NULL, ft_act, &(ph[i])))
			return (RTRN_ERROR);	
	}
	// if (pthread_create(&(data->check_death_th), NULL, ft_stop, data))
	// 		return (RTRN_ERROR);
	// pthread_detach(data->check_death_th);
	// ft_stop(data);
	ft_join_destroy(data);
	return (RTRN_SUCCESS);
}