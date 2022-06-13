/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrhyhorn <mrhyhorn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:30:42 by mrhyhorn          #+#    #+#             */
/*   Updated: 2022/06/12 16:58:44 by mrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (ft_error_msg("Invalid number of arguments"));
	memset(&data, 0, sizeof(t_data));
	if (ft_parse_input(argc, argv, &data))
		return (ft_error_msg("Error while parsing arguments"));
	if (ft_init(&data))
	{
		ft_error_msg("Initialization error");
		return (ERROR);
	}
	setbuf(stdout, NULL);
	ft_philo(&data);
	ft_free(&data);
	return (RTRN_SUCCESS);
}
