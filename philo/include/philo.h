/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:47:24 by svogrig           #+#    #+#             */
/*   Updated: 2024/09/27 20:17:19 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <stdio.h>

# define FAILURE 0
# define SUCCESS 1
# define FALSE 0
# define TRUE 1
# define FREE 0
# define IN_USE 1

typedef long			t_time_ms;
typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_timeval;

typedef struct s_arg
{
	int			nb_philo;
	int			eat_max;
	t_time_ms	time_die;
	t_time_ms	time_eat;
	t_time_ms	time_sleep;
}	t_arg;

typedef struct s_protected
{
	t_mutex	mutex;
	int		state;
}	t_protected;

typedef struct s_philo
{
	int			id;
	t_time_ms	time_die;
	t_time_ms	time_eat;
	t_time_ms	time_sleep;
	t_timeval	timeval_start;
	t_time_ms	eat_last;
	int			eat_count;
	int			eat_max;
	int			nb_philo;
	t_protected	fork;
	t_protected	*fork_1;
	t_protected	*fork_2;
	t_protected	*stop;
	t_protected	*nb_philo_eat_max;
}	t_philo;

/* arg -----------------------------------------------------------------------*/

void		arg_init(int argc, char **argv, t_arg *arg);

/* exit ----------------------------------------------------------------------*/

void		exit_on_invalid_argument(char *str);
void		exit_on_overflow(char *str);
void		exit_on_nbr_arg(void);
void		exit_on_malloc_failure(void);

/* philo_utils ---------------------------------------------------------------*/

t_time_ms	timestamp_ms(t_timeval start);
void		msleep(t_philo *philo, t_time_ms time);
int			protected_get_state(t_protected *protected);
int			check_death(t_philo	*philo);

void		*philo_loop(void *param);
t_time_ms	print_log(t_philo *philo, char *msg);

#endif
