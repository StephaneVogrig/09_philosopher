/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:43:00 by svogrig           #+#    #+#             */
/*   Updated: 2024/07/03 16:45:20 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_ulong	timestamp_in_ms(t_timeval start)
{
	struct timeval	end;
	t_ulong			time_ms;

	gettimeofday(&end, NULL);
	time_ms = (end.tv_sec - start.tv_sec) * 1000;
	time_ms += (end.tv_usec - start.tv_usec) / 1000;
	return (time_ms);
}

void	take_fork(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->fork_left);
		printf("%lu %lu has taken a fork left\n", timestamp_in_ms(philo->arg->timeval_start), philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->fork_right);
		printf("%lu %lu has taken a fork right\n", timestamp_in_ms(philo->arg->timeval_start), philo->id);
	}
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->fork_right);
		printf("%lu %lu has taken a fork right\n", timestamp_in_ms(philo->arg->timeval_start), philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->fork_left);
		printf("%lu %lu has taken a fork left\n", timestamp_in_ms(philo->arg->timeval_start), philo->id);
	}
}

void	release_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

void	philo_eat(t_philo *philo, t_arg *arg)
{
	if (get_intmtx(&arg->stop))
		return ;
	philo->eat_last = timestamp_in_ms(arg->timeval_start);
	printf("%lu %lu is eating\n", timestamp_in_ms(arg->timeval_start), philo->id);
	usleep(arg->time_eat);
	philo->eat_counter++;
	if (philo->eat_counter == arg->nbr_eat)
	{
		pthread_mutex_lock(&arg->nbr_philo_eat_finish.mutex);
		arg->nbr_philo_eat_finish.value++;
		if (arg->nbr_philo_eat_finish.value == arg->nbr_philo)
			set_intmtx(&arg->stop, TRUE);
		pthread_mutex_unlock(&arg->nbr_philo_eat_finish.mutex);
	}
}

void	philo_sleep(t_philo *philo)
{
		printf("%lu %lu is sleeping\n", timestamp_in_ms(philo->arg->timeval_start), philo->id);
		usleep(philo->arg->time_sleep);
}

void	*philosopher(void *data)
{
	t_philo	*philo;

	philo = data;
	while (!get_intmtx(&philo->arg->stop))
	{
		take_fork(philo);
		philo_eat(philo, philo->arg);
		release_fork(philo);
		philo_sleep(philo);
			set_intmtx(&philo->arg->stop, TRUE);
	}
	return (NULL);
}

void	monitor(t_arg *arg, t_philo *philo)
{
	int			i;
	t_msecond	timestamp;

	while (1)
	{
		i = -1;
		while (++i < arg->nbr_philo)
		{
			timestamp = timestamp_in_ms(arg->timeval_start);
			if (timestamp - philo[i].eat_last >= arg->time_die)
			{
				set_intmtx(&arg->stop, TRUE);
				printf("%lu %lu died\n", timestamp, philo->id);
			}
			timestamp = timestamp_in_ms(arg->timeval_start);

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
	// monitor(arg, philo);
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
	// arg destroy mutex
	free(philo);
	free(fork); // add pthread_mutex_destroy
	return (SUCCESS);
}
