/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:43:00 by svogrig           #+#    #+#             */
/*   Updated: 2024/10/05 17:48:55 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	stop(t_philo *philo)
{
	while (philo->nb_philo--)
		sem_post(philo->sem.stop);
	exit (EXIT_SUCCESS);
}

void	wait_end(t_philo *philo)
{
	int	i;
	i = philo->nb_philo;
	while(i--)
		sem_wait(philo->sem.stop);
	printf("fin wait_end\n");
}

void	*monitor(void *param)
{
	t_philo *philo;
	
	philo = param;
	t_time_ms	time;
	t_time_ms	delta;
	
	time = timestamp_ms(philo->timeval_start);
	delta = time - philo->time_eat_last;
	while (delta > 0)
	{
		msleep(philo, delta);
		time = timestamp_ms(philo->timeval_start);
		delta = time - philo->time_eat_last;
	}
	sem_wait(philo->sem.print);
	printf("%li %i died\n", time, philo->id);
	stop(philo);
	return (NULL);	
}

void	philo_run(t_philo *philo)
{
	printf("%i is created\n", philo->id);
	// pthread_t	thread;
	
	// pthread_create(&thread, NULL, &monitor, philo);
	// pthread_detach(thread);
	philo_loop(philo);
	sem_post(philo->sem.stop);
	exit (0);
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
			break;
		}
		if (philos[i] == 0)
		{
			free(philos);
			philo->id = i + 1;
			philo_run(philo);
		}
		i++;
	}
}

void	philo_init(t_philo *philo)
{
	philo->time_eat_last = 0;
	philo->eat_count = 0;
}

void	philo_clean(pid_t *philos, int n)
{
	int	i;

	i = n;
	while (i--)
	{
		kill(philos[i], SIGKILL);
		// waitpid(philos[i], NULL, 0);
	}
}

int	main(int argc, char **argv)
{
	t_philo	philo;
	pid_t	*philos;
	int		exit_code;

	exit_code = EXIT_SUCCESS;
	if (argc > 6 || argc < 5)
		exit_on_nbr_arg();
	arg_init(argc, argv, &philo);
	if (philo.nb_philo == 0)
		return (EXIT_SUCCESS);
	philos = malloc(philo.nb_philo * sizeof(*philos));
	if (!philos)
	{
		printf("philo: main: malloc: out of memory\n");
		return (EXIT_FAILURE);
	}
	if (semaphore_init(&philo.sem, philo.nb_philo) == SUCCESS)
	{
		philo_init(&philo);
		simulation_start(&philo, philos);
		wait_end(&philo);
		philo_clean(philos, philo.nb_philo);
	}
	else
		exit_code = EXIT_FAILURE;
	semaphore_clean(&philo.sem);
	free(philos);
	printf("nice job\n"); // debug
	return (exit_code);
}
