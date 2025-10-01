#include "philosophers.h"

static int	is_positive_number(char *str)
{
	int	i;

	i = 0;
	if (!str[0])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')    //contains non-digit
			return (0);
		i++;
	}
	if (i == 1 && str[0] == '0')       //the string contains exactly one character and its 0
		return (0);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_shared	shared;
	pthread_t	death_monitor_thread;
	int			i;
	int			j;

	if (argc != 5 && argc != 6)
	{
		write(2, "Error\nInvalid number of arguments\n", 34);
		return (1);
	}
	i = 0;
	while (i < argc - 1)
	{
		if (!is_positive_number(argv[i + 1]))
		{
			write(2, "Error\nInvalid input\n", 20);
			return(1);
		}
		i++;
	}
	if (init_shared(argv, argc, &shared) || init_mutexes(&shared)
		|| init_philosophers(&shared))
	{
		free(shared.philosophers);
		free(shared.forks);
		return (1);
	}
	i = 0;
	shared.start_time = get_time_in_milliseconds();         //we set the start time when the simulation starts
	//after this we need to initialize the last_meal_time of each philosopher with this start time
	//(*thats why we dont initilize it in the init_philosophers)
	while (i < shared.number_of_philosophers)
	{
		shared.philosophers[i].last_meal_time = shared.start_time;
		shared.philosophers[i].meals_eaten = 0;
		i++;
	}
	i = 0;
	while (i < shared.number_of_philosophers)
	{
		//starting all philosopher threads
		if (pthread_create(&shared.philosophers[i].thread, NULL, routine, &shared.philosophers[i]))
		{
			write(2, "Thread creation failed\n", 23);
			free(shared.philosophers);
			free(shared.forks);
			return (1);
		}
		i++;
	}
	//creating the death monitor thread
	if (pthread_create(&death_monitor_thread, NULL, death_monitor, &shared))
	{
		write(2, "Death monitor thread creation failed\n", 37);
		free(shared.philosophers);
		free(shared.forks);
		return (1);
	}
	pthread_join(death_monitor_thread, NULL);
	j = 0;
	while (j < shared.number_of_philosophers)
	{
		pthread_join(shared.philosophers[j].thread, NULL);
		j++;
	}
	free(shared.philosophers);
	free(shared.forks);
}