/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:43:00 by svogrig           #+#    #+#             */
/*   Updated: 2024/09/30 21:14:30 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_clean(t_philo *philo, int n, t_protected *stop, \
					t_protected *leftover_eater)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&philo[i].fork.mutex);
		i++;
	}
	pthread_mutex_destroy(&stop->mutex);
	pthread_mutex_destroy(&leftover_eater->mutex);
}

void	philo_run(t_philo *philo, int n)
{
	pthread_t	*thread;
	int			i;

	thread = malloc(n * sizeof(*thread));
	if (!thread)
	{
		printf("philo: philo_run: malloc: out of memory\n");
		return ;
	}
	i = 0;
	while (i < n)
	{
		if (pthread_create(&thread[i], NULL, &philo_loop, &philo[i]) != 0)
			break ;
		i++;
	}
	i = 0;
	while (i < n)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	free(thread);
}

void	fork_init(t_philo *philo, int i, int n)
{
	pthread_mutex_init(&philo[i].fork.mutex, NULL);
	philo[i].fork.state = FREE;
	philo[i].fork_left = &philo[i].fork;
	if (n == 1)
		philo[0].fork_right = NULL;
	else if (i == 0)
		philo[0].fork_right = &philo[n - 1].fork;
	else
		philo[i].fork_right = &philo[i - 1].fork;
}

void	philo_init(t_philo *philo, t_arg *arg, t_protected *stop, \
					t_protected *leftover_eater)
{
	int	i;

	pthread_mutex_init(&stop->mutex, NULL);
	stop->state = FALSE;
	pthread_mutex_init(&leftover_eater->mutex, NULL);
	leftover_eater->state = arg->nb_philo;
	i = 0;
	while (i < arg->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].time_die = arg->time_die;
		philo[i].time_eat = arg->time_eat;
		philo[i].time_sleep = arg->time_sleep;
		gettimeofday(&philo[i].timeval_start, NULL);
		philo[i].eat_last = 0;
		philo[i].eat_count = 0;
		philo[i].eat_max = arg->eat_max;
		philo[i].nb_philo = arg->nb_philo;
		fork_init(philo, i, arg->nb_philo);
		philo[i].stop = stop;
		philo[i].leftover_eater = leftover_eater;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_arg		arg;
	t_philo		*philo;
	t_protected	stop;
	t_protected	leftover_eater;

	if (argc > 6 || argc < 5)
		exit_on_nbr_arg();
	arg_init(argc, argv, &arg);
	if (arg.nb_philo == 0)
		return (EXIT_SUCCESS);
	philo = malloc(arg.nb_philo * sizeof(*philo));
	if (philo == NULL)
		exit_on_malloc_failure();
	philo_init(philo, &arg, &stop, &leftover_eater);
	philo_run(philo, arg.nb_philo);
	philo_clean(philo, arg.nb_philo, &stop, &leftover_eater);
	free(philo);
	return (EXIT_SUCCESS);
}
