/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 20:01:24 by svogrig           #+#    #+#             */
/*   Updated: 2024/10/05 21:31:58 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static inline int	is_blank(char c)
{
	return ((9 <= c && c <= 13) || c == ' ');
}

static inline int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_atoi(char *str)
{
	char	*temp;
	long	value;

	if (*str == '\0')
		exit_on_invalid_argument(str);
	temp = str;
	value = 0;
	while (is_blank(*temp))
		temp++;
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
	return ((int)value);
}

void	arg_init(int argc, char **argv, t_philo *philo)
{
	if (argc > 6 || argc < 5)
		exit_on_nbr_arg();
	argv++;
	philo->nb_philo = (int)ft_atoi(*argv++);
	philo->time_die = ft_atoi(*argv++);
	philo->time_eat = ft_atoi(*argv++);
	philo->time_sleep = ft_atoi(*argv++);
	if (argc == 6)
		philo->eat_max = ft_atoi(*argv);
	else
		philo->eat_max = 0;
}
