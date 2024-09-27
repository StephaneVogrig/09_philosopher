/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:11:35 by svogrig           #+#    #+#             */
/*   Updated: 2024/09/27 19:30:40 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	msleep(t_philo *philo, t_time_ms time)
{
	t_time_ms 	current;
	t_time_ms	end;
	
	current = timestamp_ms(philo->timeval_start);
	end = current + time;
	while (current < end)
	{
		usleep(500);
		current = timestamp_ms(philo->timeval_start);
	}
}

t_time_ms	timestamp_ms(t_timeval start)
{
	t_timeval	end;
	t_time_ms		time_ms;

	gettimeofday(&end, NULL);
	time_ms = (end.tv_sec - start.tv_sec) * 1000;
	time_ms += (end.tv_usec - start.tv_usec) / 1000;
	return (time_ms);
}
