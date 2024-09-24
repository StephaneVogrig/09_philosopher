/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 20:04:01 by svogrig           #+#    #+#             */
/*   Updated: 2024/09/24 22:34:46 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_on_invalid_argument(char *str)
{
	printf("philo: \'%s\' invalid argument\n", str);
	exit (EXIT_SUCCESS);
}

void	exit_on_overflow(char *str)
{
	printf("philo: \'%s\' out of range [0 - %u\n", str, UINT_MAX);
	exit (EXIT_SUCCESS);
}

void	exit_on_nbr_arg(void)
{
	write(1, "usage: <number_of_philosopher> <time_to_die> ", 45);
	write(2, "<time_to_eat> <time_to_sleep> ", 30);
	write(2, "[number_of_times_each_philosopher_must_eat]\n", 44);
	exit (EXIT_SUCCESS);
}
