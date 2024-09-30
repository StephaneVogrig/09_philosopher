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

void	take_fork(t_philo *philo, t_protected *fork)
{
	while (TRUE)
	{
		if (check_death(philo) == TRUE)
			return ;
		if (fork)
		{
			pthread_mutex_lock(&fork->mutex);
			if (fork->state == FREE)
			{
				fork->state = IN_USE;
				pthread_mutex_unlock(&fork->mutex);
				break ;
			}
			pthread_mutex_unlock(&fork->mutex);
		}
		usleep(10);
	}
	print_log(philo, "has taken a fork");
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
	int	temp;

	temp = 0;
	philo->eat_last = print_log(philo, "is eating");
	philo->eat_count++;
	if (philo->eat_count == philo->eat_max)
	{
		pthread_mutex_lock(&philo->leftover_eater->mutex);
		philo->leftover_eater->state--;
		temp = philo->leftover_eater->state;
		pthread_mutex_unlock(&philo->leftover_eater->mutex);
		if (temp == 0)
		{
			pthread_mutex_lock(&philo->stop->mutex);
			philo->stop->state = TRUE;
			pthread_mutex_unlock(&philo->stop->mutex);
		}
	}
	msleep(philo, philo->time_eat);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		take_fork(philo, philo->fork_right);
		take_fork(philo, philo->fork_left);
	}
	else
	{
		take_fork(philo, philo->fork_left);
		take_fork(philo, philo->fork_right);
	}
}

void	*philo_loop(void *param)
{
	t_philo	*philo;

	philo = param;
	if (philo->id % 2 == 0)
		usleep(100);
	while (TRUE)
	{
		take_forks(philo);
		eat(philo);
		fork_release(philo->fork_left);
		fork_release(philo->fork_right);
		print_log(philo, "is sleeping");
		msleep(philo, philo->time_sleep);
		print_log(philo, "is thinking");
		usleep(200 + philo->nb_philo * 2);
		if (protected_get_state(philo->stop))
			break ;
	}
	return (NULL);
}
