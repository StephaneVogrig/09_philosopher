/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:43:00 by svogrig           #+#    #+#             */
/*   Updated: 2024/09/27 03:52:52 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_check_die(t_philo *philo)
{
	t_time_ms	current;
	
	current = timestamp_ms(philo->timeval_start);
	if (current - philo->eat_last >= philo->time_die)
	{
		pthread_mutex_lock(&philo->stop->mutex);
		if (philo->stop->state == FALSE)
		{
			philo->stop->state = TRUE;
			printf("%lu %i died\n", current, philo->id);
		}
		pthread_mutex_unlock(&philo->stop->mutex);
	}
	
}

void	msleep(t_philo *philo, t_time_ms time)
{
	t_time_ms 	current;
	t_time_ms	end;
	// t_time_ms	time_since_last_eat;
	
	current = timestamp_ms(philo->timeval_start);
	end = current + time;
	// time_since_last_eat = current - philo->eat_last;
	while (current < end)
	{
		usleep(500);
		current = timestamp_ms(philo->timeval_start);
	}
	// (void)philo;
	// usleep(time * 1000);
}

t_time_ms	timestamp_ms(t_timeval start)
{
	t_timeval	end;
	t_time_ms		time_ms;

	gettimeofday(&end, NULL);
	time_ms = (end.tv_sec - start.tv_sec) * 1000;
	time_ms += (end.tv_usec - start.tv_usec) / 1000;
	return (time_ms);
}

// void	monitor(t_arg *arg, t_philo *philo)
// {
// 	int			i;
// 	t_msecond	timestamp;

// 	i = 0;
// 	while (1)
// 	{
// 		pthread_mutex_lock(&arg->access);
// 		timestamp = timestamp_ms(arg->timeval_start);
// 		if (timestamp - philo[i].eat_last >= arg->time_die)
// 		{
// 			arg->stop = TRUE;
// 			printf("%lu %lu died\n", timestamp_ms(arg->timeval_start), philo[i].id);
// 		}
// 		if (arg->nbr_philo_eat_finish == arg->nbr_philo)
// 			arg->stop = TRUE;
// 		pthread_mutex_unlock(&arg->access);
// 		if (is_finish(philo))
// 			break ;
// 		if (++i >= arg->nbr_philo)
// 			i = 0;
// 	}
// }

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
	if (n == 1)
	{
		philo[0].fork_1 = &philo[0].fork;
		philo[0].fork_2 =NULL;
	}
	else if (i == 0)
	{
		philo[0].fork_1 = &philo[0].fork;
		philo[0].fork_2 = &philo[n - 1].fork;
	}
	else if (i % 2 == 1)
	{
		philo[i].fork_1 = &philo[i - 1].fork;
		philo[i].fork_2 = &philo[i].fork;
	}
	else if (i > 0)
	{
		philo[i].fork_1 = &philo[i].fork;
		philo[i].fork_2 = &philo[i - 1].fork;
	}
}

// int	protected_init(t_protected *protected, int state)
// {
// 	if (pthread_mutex_init(&protected->mutex, NULL) != 0)
// 		protected->state = state;
// 	else
// 	{
// 		protected->state = NOT_INIT;
// 		return (FAILURE);
// 	}
// 	return (SUCCESS);
// }

void	philo_init(t_philo *philo, t_arg *arg, t_protected *stop, t_protected *nb_philo_eat_max)
{
	int	i;

	pthread_mutex_init(&stop->mutex, NULL);
	stop->state = FALSE;
	pthread_mutex_init(&nb_philo_eat_max->mutex, NULL);
	nb_philo_eat_max->state = 0;
	i = 0;
	while (i < arg->nb_philo)
	{
		philo[i].id	= i + 1;
		philo[i].time_eat = arg->time_eat;
		philo[i].time_sleep = arg->time_sleep;
		gettimeofday(&philo[i].timeval_start, NULL);
		philo[i].eat_last = 0;
		philo[i].eat_count = 0;
		philo[i].eat_max = arg->eat_max;
		philo[i].nb_philo = arg->nb_philo;
		fork_init(philo, i, arg->nb_philo);
		philo[i].stop = stop;
		philo[i].nb_philo_eat_max = nb_philo_eat_max;
		i++;
	}
}

void	philo_clean(t_philo *philo, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&philo[i].fork.mutex);
		i++;
	}
	free(philo);
}

int	main(int argc, char **argv)
{
	t_arg		arg;
	t_philo		*philo;
	t_protected	stop;
	t_protected	nb_philo_eat_max;
	// t_management	manager;

	if (argc > 6 || argc < 5)
		exit_on_nbr_arg();
	arg_init(argc, argv, &arg);
	if (arg.nb_philo == 0)
		return (EXIT_SUCCESS);
	// printf("run philo: %i die: %li eat: %li sleep: %li neat: %i\n", arg.nb_philo, arg.time_die, arg.time_eat, arg.time_sleep, arg.nb_eat);
	philo = malloc(arg.nb_philo * sizeof(*philo));
	if (philo == NULL)
		exit_on_malloc_failure();
	philo_init(philo, &arg, &stop, &nb_philo_eat_max);
	philo_run(philo, arg.nb_philo);
	philo_clean(philo, arg.nb_philo);
	pthread_mutex_destroy(&stop.mutex);
	return (EXIT_SUCCESS);
}
