/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrhyhorn <mrhyhorn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:17:30 by mrhyhorn          #+#    #+#             */
/*   Updated: 2022/06/13 19:23:56 by mrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static char	*ft_strjoin(const char *s1, char *s2)
{
	char	*join;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (join == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
		join[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		join[i++] = s2[j++];
	join[i] = '\0';
	free(s2);
	return (join);
}

static int	ft_init_sems(t_data *d)
{
	sem_unlink(DEAD_SEM_NAME);
	sem_unlink(CTRL_SEM_NAME);
	sem_unlink(ALL_ATE_SEM_NAME);
	sem_unlink(PRINT_SEM_NAME);
	sem_unlink(FORKS_SEM_NAME);
	d->dead_sem = sem_open(DEAD_SEM_NAME, O_CREAT, 0666, 0);
	if (d->dead_sem == SEM_FAILED)
		return (ERROR);
	d->control_sem = sem_open(CTRL_SEM_NAME, O_CREAT, 0666, 0);
	if (d->control_sem == SEM_FAILED)
		return (ERROR);
	d->all_ate_sem = sem_open(ALL_ATE_SEM_NAME, O_CREAT, 0666, 0);
	if (d->all_ate_sem == SEM_FAILED)
		return (ERROR);
	d->print_sem = sem_open(PRINT_SEM_NAME, O_CREAT, 0666, 1);
	if (d->print_sem == SEM_FAILED)
		return (ERROR);
	d->forks_sem = sem_open(FORKS_SEM_NAME, O_CREAT, 0666, d->philo_count);
	if (d->forks_sem == SEM_FAILED)
		return (ERROR);
	return (RTRN_SUCCESS);
}

static int	ft_fill_philos(t_data *data, t_philo *ph)
{
	int		i;
	char	*name;

	data->philo = ph;
	i = -1;
	while (++i < data->philo_count)
	{
		ph[i].philo_num = i + 1;
		ph[i].eat_count = 0;
		ph[i].done_eating = 0;
		name = ft_strjoin("/philoSem", ft_itoa(i + 1));
		sem_unlink(name);
		ph[i].philo_sem = sem_open(name, O_CREAT, 0666, 1);
		if (ph[i].philo_sem == SEM_FAILED)
		{
			free(name);
			return (ERROR);
		}
		free(name);
		ph[i].data = data;
	}
	return (RTRN_SUCCESS);
}

int	ft_init(t_data *data)
{
	t_philo	*ph;

	if (ft_init_sems(data))
		return (ERROR);
	ph = malloc(sizeof(t_philo) * data->philo_count);
	if (ph == NULL)
		return (ERROR);
	if (ft_fill_philos(data, ph))
		return (ERROR);
	return (RTRN_SUCCESS);
}
