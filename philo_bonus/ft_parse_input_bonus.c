/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_input_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrhyhorn <mrhyhorn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:26:23 by mrhyhorn          #+#    #+#             */
/*   Updated: 2022/06/03 17:33:22 by mrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_validate_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] >= '0' && argv[i][j] <= '9')
				j++;
			else
				return (1);
		}
	}
	return (0);
}

int	ft_parse_input(int argc, char **argv, t_data *data)
{
	if (ft_validate_args(argc, argv))
		return (ERROR);
	data->philo_count = (int)ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		data->must_eat = (int)ft_atol(argv[5]);
	else
		data->must_eat = -1;
	if (data->philo_count < 1 || \
		data->time_to_die < 1 || \
		data->time_to_eat < 1 || \
		data->time_to_sleep < 1 || \
		data->must_eat == 0)
	{
		return (ERROR);
	}
	return (RTRN_SUCCESS);
}
