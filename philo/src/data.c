/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 20:01:24 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/02 20:38:27 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	str_to_long(char *str)
{
	char	*temp;
	long	value;
	int		digit;

	if (!*str)
		exit_on_invalid_argument("");
	value = 0;
	temp = str;
	while (*temp >= '0' && *temp <= '9')
	{
		digit = *temp - '0';
		if (value > LONG_MAX_DIV_10 || \
			(value == LONG_MAX_DIV_10 && digit > LONG_MAX_LAST_DIGIT))
			exit_on_overflow(str);
		value = value * 10 + digit;
		temp++;
	}
	if (*temp)
		exit_on_invalid_argument(str);
	return value;
}

void	data_init_with_argv(int argc, char **argv, t_phidata *data)
{
	argv++;
	data->nbr_philo = str_to_long(*argv++);
	data->time_die = str_to_long(*argv++);
	data->time_eat = str_to_long(*argv++);
	data->time_sleep = str_to_long(*argv++);
	if (argc == 6)
		data->nbr_eat = str_to_long(*argv);
	else
		data->nbr_eat = -1;
}

void	data_print(t_phidata *data)
{
	printf("nbr philo    : %li\n", data->nbr_philo);
	printf("time to die  : %li\n", data->time_die);
	printf("time to eat  : %li\n", data->time_eat);
	printf("time to sleep: %li\n", data->time_sleep);
	printf("nbr of eat   : %li\n", data->nbr_eat);
}
	