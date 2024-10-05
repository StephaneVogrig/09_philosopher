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

void	stop(t_philo *philo)
{
	while (philo->nb_philo--)
		sem_post(philo->sem.stop);
}

void	*monitor(void *param)
{
	t_philo		*philo;
	t_time_ms	time;
	t_time_ms	delta;
	t_time_ms	time_eat_last;

	philo = param;
	while (TRUE)
	{
		time = timestamp_ms(philo->timeval_start);
		sem_wait(philo->sem.eat);
		time_eat_last = philo->time_eat_last;
		sem_post(philo->sem.eat);
		delta = time - time_eat_last;
		if (delta >= philo->time_die)
			break ;
		usleep(100);
	}
	sem_wait(philo->sem.print);
	printf("%li %i died\n", time, philo->id);
	stop(philo);
	return (NULL);
}

void	eat(t_philo *philo)
{
	int	temp;

	temp = 0;
	sem_wait(philo->sem.eat);
	philo->time_eat_last = print_log(philo, "is eating");
	sem_post(philo->sem.eat);
	philo->eat_count++;
	if (philo->eat_count == philo->eat_max)
		sem_post(philo->sem.stop);
	msleep(philo, philo->time_eat);
}

void	*philo_loop(void *param)
{
	t_philo		*philo;
	pthread_t	thread;

	philo = param;
	pthread_create(&thread, NULL, &monitor, philo);
	pthread_detach(thread);
	while (TRUE)
	{
		sem_wait(philo->sem.access);
		sem_wait(philo->sem.forks);
		print_log(philo, "has taken a fork");
		sem_wait(philo->sem.forks);
		print_log(philo, "has taken a fork");
		sem_post(philo->sem.access);
		eat(philo);
		sem_post(philo->sem.forks);
		sem_post(philo->sem.forks);
		print_log(philo, "is sleeping");
		msleep(philo, philo->time_sleep);
		print_log(philo, "is thinking");
	}
	return (NULL);
}
