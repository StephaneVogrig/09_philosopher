/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:43:00 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/19 16:20:20 by svogrig          ###   ########.fr       */
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
	philo->last_eat = timestamp_in_ms();
	philo->nbr_eat = 0;
	printf("%lu %u has taken a fork\n", timestamp_in_ms(), philo->num_philo);
	printf("%lu %u is eating\n", timestamp_in_ms(), philo->num_philo);
	usleep(philo->arg->time_eat);
	printf("%lu %u is sleeping\n", timestamp_in_ms(), philo->num_philo);
	usleep(philo->arg->time_sleep);
	printf("%lu %u is thinking\n", timestamp_in_ms(), philo->num_philo);
	printf("%lu %u died\n", timestamp_in_ms(), philo->num_philo);
	return (NULL);
}

t_bool	philo_init(pthread_t **thread, t_philo	**philo, int n)
{
	*thread = malloc(n * sizeof(**thread));
	if (!*thread)
	{
		printf("philo: philo_run: malloc: out of memory\n");
		return (FAILURE);
	}
	*philo = malloc(n * sizeof(**philo));
	if (!*philo)
	{
		printf("philo: philo_run: malloc: out of memory\n");
		free(*thread);
		*thread = NULL;
		return (FAILURE);
	}
	return (SUCCESS);
}

int	philosopher_create(t_arg *arg, pthread_t *thread, t_philo *philo)
{
	unsigned int	i;

	i = 0;
	while (i < arg->nbr_philo)
	{
		philo[i].arg = arg;
		philo[i].num_philo	= i + 1;
		if (pthread_create(&thread[i], NULL, &philosopher, &philo[i]) != 0)
			break ;
		i++;
	}
	return (i);
}

void	philo_run(t_arg *arg)
{
	pthread_t		*thread;
	t_philo			*philo;
	unsigned int	i;
	unsigned int	j;

	if(philo_init(&thread, &philo, arg->nbr_philo) == FAILURE)
		return ;
	i = philosopher_create(arg, thread, philo);
	j = 0;
	while (j < i)
	{
		pthread_join(thread[j], NULL);
		j++;
	}
	free(thread);
	free(philo);
}

int	main(int argc, char **argv)
{
	t_arg	arg;

	if (argc > 6 || argc < 5)
		exit_on_nbr_arg();
	arg_init(argc, argv, &arg);
	arg_print(&arg);
	philo_run(&arg);
	return (SUCCESS);
}
