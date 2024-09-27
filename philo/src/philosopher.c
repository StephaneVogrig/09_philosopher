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
	t_time_ms	time;

	pthread_mutex_lock(&philo->stop->mutex);
	if (philo->stop->state == FALSE)
	{
		time = timestamp_ms(philo->timeval_start);
		printf("%li %i %s\n", time, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->stop->mutex);
}

int	protected_get_state(t_protected *protected)
{
	int	state;
	
	pthread_mutex_lock(&protected->mutex);
	state = protected->state;
	pthread_mutex_unlock(&protected->mutex);
	return (state);
}

void	take_fork(t_philo *philo, t_protected *fork)
{
	int	waiting_fork;

	if (fork == NULL)
		return;
		// msleep(philo, philo->time_die);
	waiting_fork = TRUE;
	while (waiting_fork)
	{
		// if (protected_get_state(philo->stop))
		// 	return ;
		pthread_mutex_lock(&fork->mutex);
		if (fork->state == FREE)
		{
			fork->state = IN_USE;
			waiting_fork = FALSE;
			print_log(philo, "has taken a fork");
		}
		pthread_mutex_unlock(&fork->mutex);
		// philo_check_die(philo);
		if (waiting_fork)
		{
			usleep(10);
			// print_log(philo, "in loop");
		}
	}
}

// void	philo_eat(t_philo *philo, t_arg *arg)
// {
// 	t_msecond	time;

// 	time = print_log(philo, "is eating");
//     pthread_mutex_lock(&arg->access);
// 	philo->eat_last = time;
// 	philo->eat_counter++;
// 	if (philo->eat_counter == arg->nbr_eat)
// 	{
// 		arg->nbr_philo_eat_finish++;
// 	}   
//     pthread_mutex_unlock(&arg->access);
// 	msleep(philo, philo->time_eat);
// }

// void	*philosopher(void *data)
// {
// 	t_philo	*philo;

// 	philo = data;
// 	while (!is_finish(philo))
// 	{
// 		print_log(philo, "is thinking");
// 		take_fork(philo, philo->fork_1);
// 		take_fork(philo, philo->fork_2);
// 		philo_eat(philo, philo->arg);
// 		pthread_mutex_unlock(philo->fork_1);
// 		if (philo->fork_2)
// 			pthread_mutex_unlock(philo->fork_2);
// 		print_log(philo, "is sleeping");
// 		msleep(philo, philo->time_sleep);
// 	}
// 	return (NULL);
// }

void	fork_release(t_philo *philo, t_protected *fork)
{
	if (!fork)
		return;
	pthread_mutex_lock(&fork->mutex);
		fork->state = FREE;
	pthread_mutex_unlock(&fork->mutex);
	(void)philo;
	// print_log(philo, "fork release");

}

void	eat_count_manage(t_philo *philo)
{
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
}

void	*philo_loop(void *param)
{
	t_philo	*philo;
	
	philo = param;
	while (TRUE)
	{
		print_log(philo, "is thinking");
		usleep(10);
		take_fork(philo, philo->fork_1);
		take_fork(philo, philo->fork_2);
		print_log(philo, "is eating");

		eat_count_manage(philo);

		msleep(philo, philo->time_eat);
		fork_release(philo, philo->fork_1);
		fork_release(philo, philo->fork_2);
		print_log(philo, "is sleeping");
		msleep(philo, philo->time_sleep);
		if (protected_get_state(philo->stop))
			break;
	}
	return (NULL);
}
