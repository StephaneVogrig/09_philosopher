/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 20:01:24 by svogrig           #+#    #+#             */
/*   Updated: 2024/07/07 14:39:16 by svogrig          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philo.h"

static inline int	is_blank(char c)
{
	return ((9 <= c && c <= 13) || c == ' ');
}

static inline int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static unsigned long	str_to_ulong(char *str)
{
	char			*temp;
	unsigned long	value;

	if (!*str)
		exit_on_invalid_argument("");
	temp = str;
	while (is_blank(*temp))
		temp++;
	value = 0;
	while (is_digit(*temp))
	{
		value = value * 10 + *temp - '0';
		if (value > INT_MAX)
			exit_on_overflow(str);
		temp++;
	}
	while (is_blank(*temp))
		temp++;
	if (*temp)
		exit_on_invalid_argument(str);
	return value;
}

void	arg_init(int argc, char **argv, t_arg *arg)
{
	t_ulong		nbr_eat;
	t_timeval	timeval_start;

	argv++;
	arg->nbr_philo = (int)str_to_ulong(*argv++);
	arg->time_die = str_to_ulong(*argv++);
	arg->time_eat = str_to_ulong(*argv++);
	arg->time_sleep = str_to_ulong(*argv++);
	if (argc == 6)
	{
		nbr_eat = str_to_ulong(*argv);
		if (nbr_eat > INT_MAX || nbr_eat < 1)
		{
			printf("Numbrer of eat must be between 1 and %i\n", INT_MAX);
			exit(EXIT_SUCCESS);
		}
		arg->nbr_eat = (int)nbr_eat;
	}
	else
		arg->nbr_eat = 0;
	gettimeofday(&timeval_start, NULL);
	arg->timeval_start = timeval_start;
	arg->stop.value = FALSE;
	pthread_mutex_init(&(arg->stop.mutex), NULL);
	arg->nbr_philo_eat_finish.value = 0;
	pthread_mutex_init(&(arg->nbr_philo_eat_finish.mutex), NULL);
	// arg_print(arg);
}

void	arg_print(t_arg *arg)
{
	// printf("ULONG_MAX: %lu\n", ULONG_MAX);
	// printf("UINT_MAX: %u\n", UINT_MAX);
	printf("nbr philo    : %d\n", arg->nbr_philo);
	printf("time to die  : %lu\n", arg->time_die);
	printf("time to eat  : %lu\n", arg->time_eat);
	printf("time to sleep: %lu\n", arg->time_sleep);
	printf("nbr of eat   : %d\n", arg->nbr_eat);
}
	