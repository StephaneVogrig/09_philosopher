/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:52:45 by svogrig           #+#    #+#             */
/*   Updated: 2024/07/07 18:11:29 by svogrig          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philo.h"

void	print_log(t_philo *philo, char *msg)
{
	t_msecond	time;

	if (is_finish(philo))
		return ;
	pthread_mutex_lock(&philo->arg->access);
	time = timestamp_ms(philo->arg->timeval_start);
	printf("%lu %lu %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->arg->access);
}

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
	print_log(philo, "has taken a fork");
}

void	philo_eat(t_philo *philo, t_arg *arg)
{

	print_log(philo, "is eating");
	if (is_finish(philo))
		return ;
    pthread_mutex_lock(&arg->access);
	philo->eat_counter++;
	if (philo->eat_counter == arg->nbr_eat)
	{
		arg->nbr_philo_eat_finish++;
	}   
    pthread_mutex_unlock(&arg->access);
	msleep(philo, arg->time_eat);
}

void	*philosopher(void *data)
{
	t_philo	*philo;

	philo = data;
	while (!is_finish(philo))
	{
		print_log(philo, "is thinking");
		take_fork(philo, philo->fork_1);
		take_fork(philo, philo->fork_2);
		philo_eat(philo, philo->arg);
		pthread_mutex_unlock(philo->fork_1);
		if (philo->fork_2)
			pthread_mutex_unlock(philo->fork_2);
		print_log(philo, "is sleeping");
		msleep(philo, philo->arg->time_sleep);
	}
	return (NULL);
}
