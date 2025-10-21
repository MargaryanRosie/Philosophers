/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romargar <rosie.margaryan@mail.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:05:22 by romargar          #+#    #+#             */
/*   Updated: 2025/10/21 15:28:01 by romargar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_shared(char *argv[], int argc, t_shared *shared)
{
	shared->number_of_philosophers = ft_atoi(argv[1]);
	shared->time_to_die = ft_atoi(argv[2]);
	shared->time_to_eat = ft_atoi(argv[3]);
	shared->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		shared->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		shared->number_of_times_each_philosopher_must_eat = -1;
	if (shared->number_of_philosophers <= 0 || shared->time_to_die < 0
		|| shared->time_to_eat < 0
		|| shared->time_to_sleep < 0
		|| (argc == 6 && shared->number_of_times_each_philosopher_must_eat < 0))
	{
		write(2, "Error\nInvalid argument value\n", 29);
		return (1);
	}
	pthread_mutex_init(&shared->print_mutex, NULL);
	pthread_mutex_init(&shared->death_mutex, NULL);
	pthread_mutex_init(&shared->last_meal_mutex, NULL);
	return (0);
}

static int	init_all_forks(t_shared *shared, int num_of_philo)
{
	int	i;

	i = 0;
	while (i < num_of_philo)
	{
		if (pthread_mutex_init(&shared->forks[i], NULL) != 0)
		{
			i--;
			while (i >= 0)
			{
				pthread_mutex_destroy(&shared->forks[i]);
				i--;
			}
			free (shared->forks);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_mutexes(t_shared *shared)
{
	shared->forks = malloc (sizeof(pthread_mutex_t)
			* shared->number_of_philosophers);
	if (!shared->forks)
		return (1);
	if (init_all_forks(shared, shared->number_of_philosophers))
	{
		free(shared->forks);
		return (1);
	}
	return (0);
}

int	init_philosophers(t_shared *shared)
{
	int	i;

	shared->philosophers = malloc (sizeof(t_philosopher)
			* shared->number_of_philosophers);
	if (!shared->philosophers)
		return (1);
	i = 0;
	while (i < shared->number_of_philosophers)
	{
		shared->philosophers[i].id = i + 1;
		shared->philosophers[i].shared = shared;
		shared->philosophers[i].left_fork = &(shared->forks[i]);
		shared->philosophers[i].right_fork = &(shared->forks[(i + 1)
				% shared->number_of_philosophers]);
		i++;
	}
	return (0);
}
