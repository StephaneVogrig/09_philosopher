/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:11:35 by svogrig           #+#    #+#             */
/*   Updated: 2024/10/06 19:40:13 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_time_ms	print_log(t_philo *philo, char *msg)
{
	t_time_ms	time;

	sem_wait(philo->sem.eat_all);
	sem_post(philo->sem.eat_all);
	time = get_time_ms(philo->timeval_start);
	sem_wait(philo->sem.print);
	printf("%li %i %s\n", time, philo->id, msg);
	sem_post(philo->sem.print);
	return (time);
}

void	msleep(t_philo *philo, t_time_ms time)
{
	t_time_ms	current;
	t_time_ms	end;

	current = get_time_ms(philo->timeval_start);
	end = current + time;
	while (current < end)
	{
		usleep(100);
		current = get_time_ms(philo->timeval_start);
	}
}

t_time_ms	get_time_ms(t_timeval start)
{
	t_timeval	end;
	t_time_ms	time_ms;

	gettimeofday(&end, NULL);
	time_ms = (end.tv_sec - start.tv_sec) * 1000;
	time_ms += (end.tv_usec - start.tv_usec) / 1000;
	return (time_ms);
}

void	stop(t_philo *philo)
{
	while (philo->nb_philo--)
		sem_post(philo->sem.stop);
}
