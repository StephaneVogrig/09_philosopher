/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:43:00 by svogrig           #+#    #+#             */
/*   Updated: 2024/10/05 23:29:16 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_end(t_philo *philo)
{
	int	i;

	i = philo->nb_philo;
	while (i--)
		sem_wait(philo->sem.stop);
}

void	simulation_start(t_philo *philo, pid_t *philos)
{
	int		i;

	gettimeofday(&philo->timeval_start, NULL);
	i = 0;
	while (i < philo->nb_philo)
	{
		philos[i] = fork();
		if (philos[i] == -1)
		{
			printf("philo_bonus: philo_run: fork: No child created\n");
			break ;
		}
		if (philos[i] == 0)
		{
			free(philos);
			philo->id = i + 1;
			philo_loop(philo);
		}
		i++;
	}
}

void	philo_clean(pid_t *philos, int n)
{
	int	i;

	i = n;
	while (i--)
	{
		kill(philos[i], SIGKILL);
		waitpid(philos[i], NULL, 0);
	}
}

int	main(int argc, char **argv)
{
	t_philo	philo;
	pid_t	*philos;
	int		exit_code;

	exit_code = EXIT_SUCCESS;
	arg_init(argc, argv, &philo);
	if (philo.nb_philo == 0)
		return (EXIT_SUCCESS);
	philos = malloc(philo.nb_philo * sizeof(*philos));
	if (!philos)
		exit_on_malloc_failure("philo_bonus: main");
	if (semaphore_init(&philo.sem, philo.nb_philo) == SUCCESS)
	{
		philo.time_eat_last = 0;
		philo.eat_count = 0;
		simulation_start(&philo, philos);
		wait_end(&philo);
		philo_clean(philos, philo.nb_philo);
	}
	else
		exit_code = EXIT_FAILURE;
	semaphore_clean(&philo.sem);
	free(philos);
	return (exit_code);
}
