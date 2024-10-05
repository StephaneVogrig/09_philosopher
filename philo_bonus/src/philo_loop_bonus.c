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

#include "philo_bonus.h"

void	release_fork(t_philo *philo)
{
	sem_post(philo->sem.forks);
}

void	eat(t_philo *philo)
{
	int	temp;

	temp = 0;
	philo->time_eat_last = print_log(philo, "is eating");
	// printf("eat_count: %i ",philo->eat_count);
	philo->eat_count++;
	// printf("eat_count: %i eat_max: %i\n",philo->eat_count, philo->eat_max);
	if (philo->eat_count == philo->eat_max)
	{
		sem_post(philo->sem.stop);
		// printf("stop envoye\n");
	}
	msleep(philo, philo->time_eat);
}

void	take_fork(t_philo *philo)
{
	sem_wait(philo->sem.forks);
	print_log(philo, "has taken a fork");
}

void	*philo_loop(void *param)
{
	(void)param;
	t_philo	*philo;

	philo = param;
	while (TRUE)
	{
		sem_wait(philo->sem.access);
		take_fork(philo);
		take_fork(philo);
		sem_post(philo->sem.access);
		eat(philo);
		release_fork(philo);
		release_fork(philo);
		print_log(philo, "is sleeping");
		msleep(philo, philo->time_sleep);
		print_log(philo, "is thinking");
	}
	return (NULL);
}
