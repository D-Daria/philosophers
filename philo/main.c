/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrhyhorn <mrhyhorn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 16:06:33 by mrhyhorn          #+#    #+#             */
/*   Updated: 2022/05/26 20:56:08 by mrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (ft_error_msg("Invalid number of arguments"));
	memset(&data, 0, sizeof(t_data));
	if (ft_parse_input(argc, argv, &data) == RTRN_ERROR)
		return (ft_error_msg("Invalid arguments"));
	if (ft_init(&data) == RTRN_ERROR)
	{
		ft_free(&data);
		return (ft_error_msg("Initialization failed"));
	}
	if (ft_philo(&data) == RTRN_ERROR)
		ft_error_msg("Error in threads");
	ft_free(&data);
	return (RTRN_SUCCESS);
}
