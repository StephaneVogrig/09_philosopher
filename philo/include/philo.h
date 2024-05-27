/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:47:24 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/02 20:35:07 by svogrig          ###   ########.fr       */
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

# define LONG_MAX_DIV_10 922337203685477580
# define LONG_MAX_LAST_DIGIT 7

/* data ----------------------------------------------------------------------*/

typedef struct s_phidata{
	long		nbr_philo;
	suseconds_t	time_die;
	suseconds_t	time_eat;
	suseconds_t	time_sleep;
	long		nbr_eat;
}	t_phidata;

void	data_print(t_phidata *data);
void	data_init_with_argv(int argc, char **argv, t_phidata *data);

/* exit ----------------------------------------------------------------------*/

void	exit_on_invalid_argument(char *str);
void	exit_on_overflow(char *str);
void	exit_on_nbr_arg(void);

#endif