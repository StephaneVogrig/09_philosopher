/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:52:45 by svogrig           #+#    #+#             */
/*   Updated: 2024/07/07 17:32:59 by svogrig          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philo.h"

void	take_fork(t_philo *philo, t_mutex *fork)
{
	if (is_finish(philo))
		return ;
	if (fork == NULL)
	{
		msleep(philo, philo->arg->time_die);
        set_finish(philo);
		return ;
	}
	pthread_mutex_lock(fork);
	if (is_finish(philo))
		return ;
    pthread_mutex_lock(&philo->arg->access);
	printf("%lu %lu has taken a fork\n", timestamp_ms(philo->arg->timeval_start), philo->id);
    pthread_mutex_unlock(&philo->arg->access);
}

void	philo_eat(t_philo *philo, t_arg *arg)
{
	if (is_finish(philo))
		return ;
    pthread_mutex_lock(&arg->access);
	philo->eat_last = timestamp_ms(arg->timeval_start);
	printf("%lu %lu is eating\n", philo->eat_last, philo->id);
	philo->eat_counter++;
	if (philo->eat_counter == arg->nbr_eat)
	{
		arg->nbr_philo_eat_finish.value++;
		if (arg->nbr_philo_eat_finish.value == arg->nbr_philo)
			set_finish(philo);
	}   
    pthread_mutex_unlock(&arg->access);
	msleep(philo, arg->time_eat);
}

void	philo_sleep(t_philo *philo, t_arg *arg)
{	
	if (is_finish(philo))
		return ;
    pthread_mutex_lock(&arg->access);
	printf("%lu %lu is sleeping\n", timestamp_ms(philo->arg->timeval_start), philo->id);
    pthread_mutex_unlock(&arg->access);
	msleep(philo, arg->time_sleep);
}

void	philo_think(t_philo *philo)
{
	if (is_finish(philo))
		return ;
    pthread_mutex_lock(&philo->arg->access);
	printf("%lu %lu is thinking\n", timestamp_ms(philo->arg->timeval_start), philo->id);
    pthread_mutex_unlock(&philo->arg->access);
}

void	*philosopher(void *data)
{
	t_philo	*philo;

	philo = data;
	while (!is_finish(philo))
	{
		philo_think(philo);
		take_fork(philo, philo->fork_1);
		take_fork(philo, philo->fork_2);
		philo_eat(philo, philo->arg);
		pthread_mutex_unlock(philo->fork_1);
		if (philo->fork_2)
			pthread_mutex_unlock(philo->fork_2);
		philo_sleep(philo, philo->arg);
	}
	return (NULL);
}
