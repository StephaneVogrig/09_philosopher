/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 20:04:01 by svogrig           #+#    #+#             */
/*   Updated: 2024/09/26 02:41:35 by svogrig          ###   ########.fr       */
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
	printf("philo: \'%s\' out of range [0 - %u]\n", str, INT_MAX);
	exit (EXIT_SUCCESS);
}

void	exit_on_nbr_arg(void)
{
	printf("usage: <number_of_philosopher> <time_to_die> ");
	printf("<time_to_eat> <time_to_sleep> ");
	printf("[number_of_times_each_philosopher_must_eat]\n");
	exit (EXIT_SUCCESS);
}

void	exit_on_malloc_failure(void)
{
	printf("philo: malloc: out of memory\n");
	exit (EXIT_FAILURE);
}
