#include "philosophers.h"

void	*death_monitor(void *arg)
{
	t_shared	*shared;
	int			i;
	long long	time_since_last_meal;
	int			count;

	shared = (t_shared*)arg;
	while (1)
	{	
		i = 0;
		if (shared->number_of_times_each_philosopher_must_eat == -1)
		{
			while (i < shared->number_of_philosophers)
			{
				pthread_mutex_lock(&shared->last_meal_mutex);
				time_since_last_meal = get_time_in_milliseconds()
					- shared->philosophers[i].last_meal_time;
				pthread_mutex_unlock(&shared->last_meal_mutex);
				if (time_since_last_meal > shared->time_to_die)
				{
					pthread_mutex_lock(&shared->death_mutex);
					shared->someone_died = 1;
					pthread_mutex_unlock(&shared->death_mutex);
					pthread_mutex_lock(&shared->print_mutex);
					printf("%lld %d died\n", get_time_in_milliseconds()
						- shared->start_time, shared->philosophers[i].id);
					pthread_mutex_unlock(&shared->print_mutex);
					return (NULL);
				}
				i++;
			}
		}
		else
		{
			count = 0;
			while (i < shared->number_of_philosophers)
			{
				pthread_mutex_lock(&shared->last_meal_mutex);
        		if (shared->philosophers[i].meals_eaten >=
            	shared->number_of_times_each_philosopher_must_eat)
            	count++;
        		pthread_mutex_unlock(&shared->last_meal_mutex);
        		i++;
			}
			if (count == shared->number_of_philosophers)
			{
				pthread_mutex_lock(&shared->death_mutex);
				shared->someone_died = 1;
				pthread_mutex_unlock(&shared->death_mutex);;
				return (NULL);
			}
		}
		usleep(1000);        //lowering CPU usage
	}
	return (NULL);
}
