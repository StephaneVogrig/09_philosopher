/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:47:24 by svogrig           #+#    #+#             */
/*   Updated: 2024/07/07 11:28:03 by svogrig          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <stdio.h>

# define SUCCESS 0
# define FAILURE 1
# define FALSE 0
# define TRUE 1

typedef int t_bool;
typedef unsigned int t_uint;
typedef unsigned long t_ulong;
typedef unsigned long t_msecond;
typedef pthread_mutex_t t_mutex;
typedef struct timeval t_timeval;
typedef struct s_arg t_arg;
typedef struct s_int_mutex t_intmtx;

struct s_int_mutex{
	t_mutex	mutex;
	int		value;
};

/* arg -----------------------------------------------------------------------*/

struct s_arg{
	int			nbr_philo;
	t_msecond	time_die;
	t_msecond	time_eat;
	t_msecond	time_sleep;
	int			nbr_eat;
	t_timeval	timeval_start;
	t_intmtx	stop;
	t_intmtx	nbr_philo_eat_finish;
};

void	arg_print(t_arg *data);
void	arg_init(int argc, char **argv, t_arg *arg);

/* data ----------------------------------------------------------------------*/

typedef struct s_philo{
	t_ulong		id;
	t_mutex		*fork_1;
	t_mutex		*fork_2;
	int			eat_counter;
	t_msecond	eat_last;
	t_arg		*arg;
}	t_philo;

t_bool	data_init(t_philo **philo, t_mutex **fork, t_arg *arg);

/* exit ----------------------------------------------------------------------*/

void	exit_on_invalid_argument(char *str);
void	exit_on_overflow(char *str);
void	exit_on_nbr_arg(void);

/* intmtx */

void	set_intmtx(t_intmtx *protected, int value);
int		get_intmtx(t_intmtx *protected);

#endif