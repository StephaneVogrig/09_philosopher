/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:47:24 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/19 16:10:04 by svogrig          ###   ########.fr       */
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

typedef int t_bool;

/* arg -----------------------------------------------------------------------*/

typedef struct s_arg{
	unsigned long	nbr_philo;
	suseconds_t		time_die;
	suseconds_t		time_eat;
	suseconds_t		time_sleep;
	unsigned long			nbr_eat;
}	t_arg;

void	arg_print(t_arg *data);
void	arg_init(int argc, char **argv, t_arg *arg);

/* data ----------------------------------------------------------------------*/

typedef struct s_philo{
	t_arg			*arg;
	unsigned int	num_philo;
	time_t			last_eat;
	unsigned long	nbr_eat;
}	t_philo;

/* exit ----------------------------------------------------------------------*/

void	exit_on_invalid_argument(char *str);
void	exit_on_overflow(char *str);
void	exit_on_nbr_arg(void);

#endif