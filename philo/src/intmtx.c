/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intmtx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:11:35 by svogrig           #+#    #+#             */
/*   Updated: 2024/07/07 16:51:39 by svogrig          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philo.h"

t_bool	is_finish(t_philo *philo)
{
	if (get_intmtx(&philo->arg->stop))
		return (TRUE);
	return (FALSE);
}

void	set_finish(t_philo *philo)
{
	set_intmtx(&philo->arg->stop, TRUE);
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
