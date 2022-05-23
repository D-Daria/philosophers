/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrhyhorn <mrhyhorn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 12:31:20 by mrhyhorn          #+#    #+#             */
/*   Updated: 2022/05/23 23:23:47 by mrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_set_all_dead(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->philo_count)
	{
		pthread_mutex_lock(&(data->philo[i].dead_mutex));
		data->philo[i].is_dead = DEAD;
		pthread_mutex_unlock(&(data->philo[i].dead_mutex));
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

void	ft_set_stop(t_data *data)
{
	pthread_mutex_lock(&(data->all_dead_mutex));
	data->all_dead = 1;
	pthread_mutex_unlock(&(data->all_dead_mutex));
}

int	ft_set_eat(t_philo *ph)
{
	static int	c;

	pthread_mutex_lock(&(ph->eat_mutex));
	if (ph->done_eating == 1 && ph->data->must_eat > 0)
	{
		pthread_mutex_unlock(&(ph->eat_mutex));
		c += 1;
		ph->done_eating = -1;
	}
	if (c == ph->data->philo_count)
	{
		pthread_mutex_unlock(&(ph->eat_mutex));
		pthread_mutex_lock(&(ph->data->all_ate_mutex));
		ph->data->all_have_eaten = 1;
		pthread_mutex_unlock(&(ph->data->all_ate_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(ph->eat_mutex));
	return (0);
}

void	*ft_stop(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&(ph->dead_mutex));
		if (ft_get_time('l') - ph->tm_last_eating > ph->data->time_to_die)
		{
			pthread_mutex_unlock(&(ph->dead_mutex));
			ft_print(ph, DIED_MSG);
			ft_set_stop(ph->data);
			break ;
		}
		pthread_mutex_unlock(&(ph->dead_mutex));
		if (ft_set_eat(ph))
			break ;
		usleep(100);
		// pthread_mutex_lock(&(ph->state_mutex));
		// if (ph->done_eating == 1 && ph->data->must_eat > 0)
		// {
		// 	c += 1;
		// 	ph->done_eating = -1;
		// }
		// if (c == ph->data->philo_count)
		// {
		// 	// pthread_mutex_unlock(&(ph->state_mutex));
		// 	ph->data->all_have_eaten = 1;
		// 	break ;
		// }
		// pthread_mutex_unlock(&(ph->state_mutex));
	}
	return (NULL);
}
/*
void	*ft_eat(void *arg)
{
	t_philo	*ph;
	int		c;

	ph = (t_philo *)arg;
	c = 0;
	while (1)
	{
		pthread_mutex_lock(&(ph->state_mutex));
		if (ph->done_eating && ph->data->must_eat > 0)
		{
			ph->done_eating = -1;
			c += 1;
		}
		if (c == ph->data->philo_count)
		{
			pthread_mutex_unlock(&(ph->state_mutex));
			pthread_mutex_lock(&(ph->data->all_ate_mutex));
			ph->data->all_have_eaten = 1;
			pthread_mutex_unlock(&(ph->data->all_ate_mutex));
			break ;
		}
		pthread_mutex_unlock(&(ph->state_mutex));
	}
	return (NULL);
}
*/
int	ft_is_stop(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->all_dead_mutex));
	if (philo->data->all_dead)
	{
		pthread_mutex_unlock(&(philo->data->all_dead_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(philo->data->all_dead_mutex));
	return (0);
}

void	*ft_act(void *arg)
{
	pthread_t	dead_th;
	// pthread_t	eat_th;
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->philo_num % 2 == 0)
		usleep(100);
	if (pthread_create(&dead_th, NULL, ft_stop, philo))
		return (NULL);
	// if (philo->data->must_eat > 0)
	// {
	// 	if (pthread_create(&eat_th, NULL, ft_eat, philo))
	// 		return (NULL);
	// 	pthread_detach(eat_th);
	// }
	while (1)
	{
		if (ft_is_stop(philo) || philo->data->all_have_eaten)
			break ;
		ft_eating(philo);
		ft_sleeping(philo);
		ft_thinking(philo);
	}
	pthread_detach(dead_th);
	// pthread_mutex_unlock(&(philo->data->all_dead_mutex));
	// pthread_mutex_unlock(&(philo->data->check_mutex));
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
		ph[i].tm_last_eating = data->start_time;
		if (pthread_create(&(ph[i].thread), NULL, ft_act, &(ph[i])))
			return (RTRN_ERROR);
	}
	ft_join_destroy(data);
	return (RTRN_SUCCESS);
}