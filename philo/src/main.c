/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:43:00 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/02 20:20:53 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_phidata	data;

	if (argc > 6 || argc < 5)
		exit_on_nbr_arg();
	data_init_with_argv(argc, argv, &data);
	data_print(&data);
	return (SUCCESS);
}
