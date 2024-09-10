/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intmtx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:11:35 by svogrig           #+#    #+#             */
/*   Updated: 2024/07/07 18:13:23 by svogrig          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philo.h"

t_bool	is_finish(t_philo *philo)
{
	t_bool	finish;
	
	pthread_mutex_lock(&philo->arg->access);
	finish = philo->arg->stop;
	pthread_mutex_unlock(&philo->arg->access);
	return (finish);
}

void	set_finish(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->access);
	philo->arg->stop = TRUE;
	pthread_mutex_unlock(&philo->arg->access);
}

void	set_intmtx(t_intmtx *protected, int value)
{
	pthread_mutex_lock(&protected->mutex);
	protected->value = value;
	pthread_mutex_unlock(&protected->mutex);
}

int	get_intmtx(t_intmtx *protected)
{
	int	tmp;

	pthread_mutex_lock(&protected->mutex);
	tmp = protected->value;
	pthread_mutex_unlock(&protected->mutex);
	return (tmp);
}
