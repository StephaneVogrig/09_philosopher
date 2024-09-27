/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:36:37 by svogrig           #+#    #+#             */
/*   Updated: 2024/09/25 23:24:49 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// int	i_next(int i, t_arg *arg)
// {
// 	i++;
// 	if (i == arg->nbr_philo)
// 		return (0);
// 	return (i);
// }

// void data_fill(t_philo *philo, t_mutex *fork,  t_arg *arg)
// {
// 	int i;

// 	i = 0;
// 	while (i < arg->nbr_philo)
// 	{
// 		pthread_mutex_init(&fork[i], NULL);
// 		philo[i].id	= i + 1;
// 		philo[i].eat_counter = 0;
// 		philo[i].eat_last = 0;
// 		philo[i].time_eat = arg->time_eat;
// 		philo[i].time_sleep = arg->time_sleep;
// 		philo[i].timeval_start = arg->timeval_start;
// 		philo[i].arg = arg;
// 		philo[i].fork_1 = &fork[i];
// 		if (arg->nbr_philo == 1)
// 			philo[i].fork_2 = NULL;
// 		else if (i % 2)
// 			philo[i].fork_2 = &fork[i_next(i, arg)];
// 		else
// 		{
// 			philo[i].fork_1 = &fork[i_next(i, arg)];
// 			philo[i].fork_2 = &fork[i];
// 		}
// 		i++;
// 	}
// }

// t_bool	data_init(t_philo **philo, t_mutex **fork, t_arg *arg)
// {
// 	*philo = malloc(arg->nbr_philo * sizeof(**philo));
// 	*fork = malloc(arg->nbr_philo * sizeof(**fork));
// 	if (!*philo || !*fork)
// 	{
// 		printf("data_init: malloc: out of memory\n");
// 		if (*philo)
// 			free(*philo);
// 		if (*fork)
// 			free(*fork);
// 		return (FAILURE);
// 	}
// 	data_fill(*philo, *fork, arg);
// 	return (SUCCESS);
// }

// void	data_destroy(t_philo *philo, t_mutex *fork, t_arg *arg)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < arg->nbr_philo)
// 		pthread_mutex_destroy(&fork[i]);
// 	free(fork);
// 	free(philo);
// }