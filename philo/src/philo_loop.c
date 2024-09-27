/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 20:13:15 by svogrig           #+#    #+#             */
/*   Updated: 2024/09/27 20:13:15 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_time_ms	print_log(t_philo *philo, char *msg)
{
	t_time_ms	time;

	time = timestamp_ms(philo->timeval_start);
	pthread_mutex_lock(&philo->stop->mutex);
	if (philo->stop->state == FALSE)
	{
		printf("%li %i %s\n", time, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->stop->mutex);
	return (time);
}

void	take_fork(t_philo *philo, t_protected *fork)
{
	if (fork == NULL)
		return ;
	while (TRUE)
	{
		if (check_death(philo) == TRUE)
		{
			if (fork == philo->fork_1)
				philo->fork_1 = NULL;
			else
				philo->fork_2 = NULL;
			break ;
		}
		pthread_mutex_lock(&fork->mutex);
		if (fork->state == FREE)
		{
			fork->state = IN_USE;
			print_log(philo, "has taken a fork");
			pthread_mutex_unlock(&fork->mutex);
			break ;
		}
		pthread_mutex_unlock(&fork->mutex);
		usleep(10);
	}
}

void	fork_release(t_protected *fork)
{
	if (!fork)
		return ;
	pthread_mutex_lock(&fork->mutex);
	fork->state = FREE;
	pthread_mutex_unlock(&fork->mutex);
}

void	eat(t_philo *philo)
{
	philo->eat_last = print_log(philo, "is eating");
	philo->eat_count++;
	if (philo->eat_count == philo->eat_max)
	{
		pthread_mutex_lock(&philo->nb_philo_eat_max->mutex);
		philo->nb_philo_eat_max->state++;
		if (philo->nb_philo_eat_max->state >= philo->nb_philo)
		{
			pthread_mutex_lock(&philo->stop->mutex);
			philo->stop->state = TRUE;
			pthread_mutex_unlock(&philo->stop->mutex);
		}
		pthread_mutex_unlock(&philo->nb_philo_eat_max->mutex);
	}
	msleep(philo, philo->time_eat);
}

void	*philo_loop(void *param)
{
	t_philo	*philo;

	philo = param;
	while (TRUE)
	{
		usleep(400);
		print_log(philo, "is thinking");
		take_fork(philo, philo->fork_1);
		take_fork(philo, philo->fork_2);
		eat(philo);
		fork_release(philo->fork_1);
		fork_release(philo->fork_2);
		print_log(philo, "is sleeping");
		msleep(philo, philo->time_sleep);
		if (protected_get_state(philo->stop))
			break ;
	}
	return (NULL);
}
