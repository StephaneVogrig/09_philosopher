/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:30:23 by svogrig           #+#    #+#             */
/*   Updated: 2024/10/05 23:28:47 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	semaphore_unlink(void)
{
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_ACCESS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_STOP);
	sem_unlink(SEM_EAT);
}

void	semaphore_close(t_sem *sem)
{
	sem_close(sem->forks);
	sem_close(sem->access);
	sem_close(sem->print);
	sem_close(sem->stop);
	sem_close(sem->eat);
}

int	semaphore_init(t_sem *sem, int nb_philo)
{
	semaphore_unlink();
	sem->forks = sem_open(SEM_FORK, O_CREAT, O_RDWR, nb_philo);
	sem->access = sem_open(SEM_ACCESS, O_CREAT, O_RDWR, 1);
	sem->print = sem_open(SEM_PRINT, O_CREAT, O_RDWR, 1);
	sem->stop = sem_open(SEM_STOP, O_CREAT, O_RDWR, 0);
	sem->eat = sem_open(SEM_EAT, O_CREAT, O_RDWR, 1);
	if (sem->forks == SEM_FAILED || sem->print == SEM_FAILED \
		|| sem->print == SEM_FAILED || sem->print == SEM_FAILED)
	{
		printf("philo_bonus: semaphore_init: failed\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

void	semaphore_clean(t_sem *sem)
{
	semaphore_close(sem);
	semaphore_unlink();
}
