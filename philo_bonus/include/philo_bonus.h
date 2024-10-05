/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:47:24 by svogrig           #+#    #+#             */
/*   Updated: 2024/10/04 22:04:43 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <stdio.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <signal.h>

# define FAILURE 0
# define SUCCESS 1
# define FALSE 0
# define TRUE 1
// # define FREE 0
// # define IN_USE 1

# define SEM_FORK		"/philo_fork"
# define SEM_PRINT		"/philo_print"
# define SEM_STOP		"/philo_stop"
# define SEM_REMAIN	"/philo_remain"

typedef long			t_time_ms;
typedef struct timeval	t_timeval;

typedef struct s_arg
{
	int			nb_philo;
	int			eat_max;
	t_time_ms	time_die;
	t_time_ms	time_eat;
	t_time_ms	time_sleep;
}	t_arg;

// typedef struct s_protected
// {
// 	t_mutex	mutex;
// 	int		state;
// }	t_protected;

typedef struct s_semaphore
{
	sem_t	*forks;
	sem_t	*print;
	sem_t	*stop;
	sem_t	*access;
}	t_sem;

typedef struct s_philo
{
	int			id;
	t_time_ms	time_die;
	t_time_ms	time_eat;
	t_time_ms	time_sleep;
	t_timeval	timeval_start;
	t_time_ms	time_eat_last;
	int			eat_count;
	int			eat_max;
	int			nb_philo;
	t_sem		sem;
}	t_philo;

/* arg -----------------------------------------------------------------------*/

void	arg_init(int argc, char **argv, t_philo *philo);

/* exit ----------------------------------------------------------------------*/

void		exit_on_invalid_argument(char *str);
void		exit_on_overflow(char *str);
void		exit_on_nbr_arg(void);
// void		exit_on_malloc_failure(void);

// /* philo_utils ---------------------------------------------------------------*/

t_time_ms	timestamp_ms(t_timeval start);
void		msleep(t_philo *philo, t_time_ms time);
// int			protected_get_state(t_protected *protected);
// int			check_death(t_philo	*philo);
t_time_ms	print_log(t_philo *philo, char *msg);

/* philo_loop ----------------------------------------------------------------*/

void		*philo_loop(void *param);

/* philo_loop ----------------------------------------------------------------*/

int			semaphore_init(t_sem *sem, int nb_philo);
void		semaphore_close(t_sem *sem);
void		semaphore_clean(t_sem *sem);

#endif