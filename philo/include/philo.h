/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:47:24 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/21 17:38:21 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef pthread_mutex_t t_mutex;
typedef int t_bool;
typedef unsigned int t_uint;
typedef unsigned long t_ulong;

/* arg -----------------------------------------------------------------------*/

typedef struct s_arg{
	t_ulong		nbr_philo;
	suseconds_t	time_die;
	suseconds_t	time_eat;
	suseconds_t	time_sleep;
	t_ulong		nbr_eat;
}	t_arg;

void	arg_print(t_arg *data);
void	arg_init(int argc, char **argv, t_arg *arg);

/* data ----------------------------------------------------------------------*/

typedef struct s_philo{
	t_ulong	id;
	t_mutex	*fork_left;
	t_mutex	*fork_right;
	t_ulong	eat_counter;
	time_t	eat_last;
	t_arg	*arg;
}	t_philo;

t_bool	data_init(t_philo **philo, t_mutex **fork, t_arg *arg);

/* exit ----------------------------------------------------------------------*/

void	exit_on_invalid_argument(char *str);
void	exit_on_overflow(char *str);
void	exit_on_nbr_arg(void);

#endif