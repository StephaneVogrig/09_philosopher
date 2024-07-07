/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:52:45 by svogrig           #+#    #+#             */
/*   Updated: 2024/07/07 15:12:59 by svogrig          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philo.h"

void	take_fork(t_philo *philo, t_mutex *fork)
{
	if (is_finish(philo))
		return ;
	if (fork == NULL)
	{
		// while (!is_finish(philo))
			usleep(philo->arg->time_die * 1000);
			set_stop(philo);
		return ; // wait died
	}
	pthread_mutex_lock(fork);
	if (is_finish(philo))
		return ;
    pthread_mutex_lock(&philo->arg->access);
	printf("%lu %lu has taken a fork\n", timestamp_ms(philo->arg->timeval_start), philo->id);
    pthread_mutex_unlock(&philo->arg->access);
}

void	release_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_1);
	pthread_mutex_unlock(philo->fork_2);
}

void	philo_eat(t_philo *philo, t_arg *arg)
{
	t_msecond	last_eat;

	last_eat = philo->eat_last;
	if (is_finish(philo))
		return ;
	philo->eat_last = timestamp_ms(arg->timeval_start);
	printf("%lu %lu is eating - last eat %lu\n", philo->eat_last, philo->id, last_eat);
	philo->eat_counter++;
	if (philo->eat_counter == arg->nbr_eat)
	{
		pthread_mutex_lock(&arg->nbr_philo_eat_finish.mutex);
		arg->nbr_philo_eat_finish.value++;
		if (arg->nbr_philo_eat_finish.value == arg->nbr_philo)
			set_stop(philo);
		pthread_mutex_unlock(&arg->nbr_philo_eat_finish.mutex);
	}
	if (is_finish(philo))
		return ;
	usleep(arg->time_eat * 1000);
}

void	philo_sleep(t_philo *philo, t_arg *arg)
{	
(void)arg;
	if (is_finish(philo))
		return ;
    pthread_mutex_lock(&arg->access);
	printf("%lu %lu is sleeping\n", timestamp_ms(philo->arg->timeval_start), philo->id);
    pthread_mutex_unlock(&arg->access);
	usleep(philo->arg->time_sleep * 1000);
}

void	*philosopher(void *data)
{
	t_philo	*philo;

	philo = data;
	while (!is_finish(philo))
	{
		take_fork(philo, philo->fork_1);
		take_fork(philo, philo->fork_2);
		philo_eat(philo, philo->arg);
		release_fork(philo);
		philo_sleep(philo, philo->arg);
	}
	return (NULL);
}
