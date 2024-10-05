/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:11:35 by svogrig           #+#    #+#             */
/*   Updated: 2024/10/05 21:07:46 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_time_ms	print_log(t_philo *philo, char *msg)
{
	t_time_ms	time;

	time = timestamp_ms(philo->timeval_start);
	sem_wait(philo->sem.print);
		printf("%li %i %s\n", time, philo->id, msg);
	sem_post(philo->sem.print);
	return (time);
}

void	msleep(t_philo *philo, t_time_ms time)
{
	t_time_ms	current;
	t_time_ms	end;

	current = timestamp_ms(philo->timeval_start);
	end = current + time;
	while (current < end)
	{
		usleep(100);
		current = timestamp_ms(philo->timeval_start);
	}
}

t_time_ms	timestamp_ms(t_timeval start)
{
	t_timeval	end;
	t_time_ms	time_ms;

	gettimeofday(&end, NULL);
	time_ms = (end.tv_sec - start.tv_sec) * 1000;
	time_ms += (end.tv_usec - start.tv_usec) / 1000;
	return (time_ms);
}

// int	protected_get_state(t_protected *protected)
// {
// 	int	state;

// 	pthread_mutex_lock(&protected->mutex);
// 	state = protected->state;
// 	pthread_mutex_unlock(&protected->mutex);
// 	return (state);
// }

// int	check_death(t_philo	*philo)
// {
// 	t_time_ms	time;
// 	t_time_ms	delta;

// 	// if (protected_get_state(philo->stop) == TRUE)
// 	// 	return (TRUE);
// 	time = timestamp_ms(philo->timeval_start);
// 	delta = time - philo->time_eat_last;
// 	if (delta >= philo->time_die)
// 	{
// 		// pthread_mutex_lock(&philo->stop->mutex);
// 		// if (philo->stop->state == FALSE)
// 		// {
// 		// 	philo->stop->state = TRUE;
// 		// 	printf("%li %i died\n", time, philo->id);
// 		// }
// 		// pthread_mutex_unlock(&philo->stop->mutex);
// 		return (TRUE);
// 	}
// 	return (FALSE);
// }
