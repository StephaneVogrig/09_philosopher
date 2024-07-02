/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:43:00 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/21 18:23:13 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	timestamp_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec / 1000);
}

void	*philosopher(void *data)
{
	t_philo	*philo;

	philo = data;
	philo->eat_last = timestamp_in_ms();
	philo->eat_counter = 0;
	printf("%lu %lu has taken a fork\n", timestamp_in_ms(), philo->id);
	printf("%lu %lu is eating\n", timestamp_in_ms(), philo->id);
	usleep(philo->arg->time_eat);
	printf("%lu %lu is sleeping\n", timestamp_in_ms(), philo->id);
	usleep(philo->arg->time_sleep);
	printf("%lu %lu is thinking\n", timestamp_in_ms(), philo->id);
	printf("%lu %lu died\n", timestamp_in_ms(), philo->id);
	return (NULL);
}

void	philo_run(t_arg *arg, t_philo *philo)
{
	pthread_t	*thread;
	t_uint		i;
	t_uint		j;

	thread = malloc(arg->nbr_philo * sizeof(*thread));
	if (!thread)
	{
		printf("philo: philo_run: malloc: out of memory\n");
		return ;
	}
	i = 0;
	while (i < arg->nbr_philo)
	{
		if (pthread_create(&thread[i], NULL, &philosopher, &philo[i]) != 0)
			break ;
		i++;
	}
	j = 0;
	while (j < i)
	{
		pthread_join(thread[j], NULL);
		j++;
	}
	free(thread);
}

int	main(int argc, char **argv)
{
	t_arg	arg;
	t_philo	*philo;
	t_mutex	*fork;

	if (argc > 6 || argc < 5)
		exit_on_nbr_arg();
	arg_init(argc, argv, &arg);
	if (arg.nbr_philo == 0)
		return (EXIT_SUCCESS);
	if (data_init(&philo, &fork, &arg) == FAILURE)
		return (EXIT_FAILURE);
	philo_run(&arg, philo);
	free(philo);
	free(fork);
	return (SUCCESS);
}
