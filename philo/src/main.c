/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:43:00 by svogrig           #+#    #+#             */
/*   Updated: 2024/07/07 16:52:56 by svogrig          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philo.h"

void	msleep(t_philo *philo, t_ulong time)
{
	t_msecond 	timestamp;
	t_msecond	end;
	
	if (is_finish(philo))
		return ;
    pthread_mutex_lock(&philo->arg->access);
	timestamp = timestamp_ms(philo->arg->timeval_start);
	pthread_mutex_unlock(&philo->arg->access);
	end = timestamp + time;
	while (timestamp < end)
	{
		if (end - timestamp > 10)
			usleep(6000);
		if (is_finish(philo))
			return ;
		pthread_mutex_lock(&philo->arg->access);
		timestamp = timestamp_ms(philo->arg->timeval_start);
		pthread_mutex_unlock(&philo->arg->access);
	}
}

t_ulong	timestamp_ms(t_timeval start)
{
	struct timeval	end;
	t_ulong			time_ms;

	gettimeofday(&end, NULL);
	time_ms = (end.tv_sec - start.tv_sec) * 1000;
	time_ms += (end.tv_usec - start.tv_usec) / 1000;
	// time_ms = (end.tv_sec - start.tv_sec) * 1000 * 1000;
	// time_ms += (end.tv_usec - start.tv_usec);
	return (time_ms);
}

void	monitor(t_arg *arg, t_philo *philo)
{
	int			i;
	t_msecond	timestamp;
	t_msecond	last_eat;

	while (1)
	{
		i = -1;
		while (++i < arg->nbr_philo)
		{
			pthread_mutex_lock(&philo->arg->access);
			last_eat = philo[i].eat_last;
			timestamp = timestamp_ms(arg->timeval_start);
			t_msecond diff_time = timestamp - last_eat;
			if (diff_time >= arg->time_die)
			{
				set_finish(philo);
				printf("%lu %lu died\n", timestamp, philo[i].id);
			}
			pthread_mutex_unlock(&philo->arg->access);
			if (is_finish(philo))
				return ;
		}
	}
}

void	philo_run(t_arg *arg, t_philo *philo)
{
	pthread_t	*thread;
	int		i;

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
	monitor(arg, philo);
	i = 0;
	while (i < arg->nbr_philo)
	{
		pthread_join(thread[i], NULL);
		i++;
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
	data_destroy(philo, fork, &arg);
	return (EXIT_SUCCESS);
}
