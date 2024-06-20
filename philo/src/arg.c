/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 20:01:24 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/19 15:39:39 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline int	isblank(char c)
{
	return ((9 <= c && c <= 13) || c == ' ');
}

static inline int	isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static unsigned long	str_to_ulong(char *str)
{
	char			*temp;
	unsigned long	value;
	unsigned long	previous;

	if (!*str)
		exit_on_invalid_argument("");
	temp = str;
	while (isblank(*temp))
		temp++;
	value = 0;
	while (isdigit(*temp))
	{
		previous = value;
		value = value * 10 + *temp - '0';
		if (value > UINT_MAX)
			exit_on_overflow(str);
		temp++;
	}
	while (isblank(*temp))
		temp++;
	if (*temp)
		exit_on_invalid_argument(str);
	return value;
}

void	arg_init(int argc, char **argv, t_arg *arg)
{
	argv++;
	arg->nbr_philo = str_to_ulong(*argv++);
	arg->time_die = str_to_ulong(*argv++) * 1000;
	arg->time_eat = str_to_ulong(*argv++) * 1000;
	arg->time_sleep = str_to_ulong(*argv++) * 1000;
	if (argc == 6)
		arg->nbr_eat = str_to_ulong(*argv);
	else
		arg->nbr_eat = -1;
}

void	arg_print(t_arg *arg)
{
	printf("ULONG_MAX: %lu\n", ULONG_MAX);
	printf("UINT_MAX: %u\n", UINT_MAX);
	printf("nbr philo    : %lu\n", arg->nbr_philo);
	printf("time to die  : %lu\n", arg->time_die);
	printf("time to eat  : %lu\n", arg->time_eat);
	printf("time to sleep: %lu\n", arg->time_sleep);
	printf("nbr of eat   : %lu\n", arg->nbr_eat);
}
	