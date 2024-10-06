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
		time = get_time_ms(philo->timeval_start);
		sem_wait(philo->sem.eat_last);
		time_eat_last = philo->time_eat_last;
		sem_post(philo->sem.eat_last);
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

void	take_forks(t_philo *philo)
{
	sem_wait(philo->sem.access);
	sem_wait(philo->sem.forks);
	print_log(philo, "has taken a fork");
	sem_wait(philo->sem.forks);
	print_log(philo, "has taken a fork");
	sem_post(philo->sem.access);
}

void	eat(t_philo *philo)
{
	int	temp;

	temp = 0;
	sem_wait(philo->sem.eat_last);
	philo->time_eat_last = print_log(philo, "is eating");
	sem_post(philo->sem.eat_last);
	msleep(philo, philo->time_eat);
	philo->eat_count++;
	if (philo->eat_count == philo->eat_max)
		sem_post(philo->sem.stop);
}

void	philo_loop(t_philo	*philo)
{
	pthread_t	thread;

	if (pthread_create(&thread, NULL, &monitor, philo) != 0)
	{
		printf("philo_loop_bonus: philo_loop: pthread_create: failure\n");
		stop(philo);
		exit (EXIT_FAILURE);
	}
	pthread_detach(thread);
	while (TRUE)
	{
		take_forks(philo);
		eat(philo);
		sem_post(philo->sem.forks);
		sem_post(philo->sem.forks);
		print_log(philo, "is sleeping");
		msleep(philo, philo->time_sleep);
		print_log(philo, "is thinking");
	}
}
