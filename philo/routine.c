#include "philosophers.h"

void	precise_usleep(long duration_in_ms)
{
	long	start_time;

	start_time = get_time_in_milliseconds();
	while (get_time_in_milliseconds() - start_time < duration_in_ms)
		usleep(100);
}

static void	print_state(t_philosopher *philo, char *message)
{
	pthread_mutex_lock(&philo->shared->death_mutex);
	pthread_mutex_lock(&philo->shared->print_mutex);
	if (philo->shared->someone_died != 1)
		printf("%lld %d %s", get_time_in_milliseconds()
			- philo->shared->start_time, philo->id, message);
	pthread_mutex_unlock(&philo->shared->print_mutex);
	pthread_mutex_unlock(&philo->shared->death_mutex);
}

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	//special case for 1 philosopher, cause it will wait forever for the second fork
	if (philo->shared->number_of_philosophers == 1)
	{
		print_state(philo, "has taken a fork\n");
		precise_usleep(philo->shared->time_to_die);
		print_state(philo, "died\n");
		return (NULL);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->shared->death_mutex);    //when monitor writes, other threads read this data, so needs protection
		if (philo->shared->someone_died == 1)
		{
			pthread_mutex_unlock(&philo->shared->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->shared->death_mutex);
		if (philo->id % 2 != 0)
		{
			pthread_mutex_lock(philo->right_fork);
			print_state(philo, "has taken a fork\n");
			pthread_mutex_lock(philo->left_fork);
			print_state(philo, "has taken a fork\n");
		}
		else
		{
			pthread_mutex_lock(philo->left_fork);
			print_state(philo, "has taken a fork\n");
			pthread_mutex_lock(philo->right_fork);
			print_state(philo, "has taken a fork\n");
		}
		pthread_mutex_lock(&philo->shared->last_meal_mutex);
		philo->last_meal_time = get_time_in_milliseconds();
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->shared->last_meal_mutex);
		print_state(philo, "is eating\n");
		precise_usleep(philo->shared->time_to_eat);
		if (philo->id % 2 != 0)
		{
    		pthread_mutex_unlock(philo->left_fork);
    		pthread_mutex_unlock(philo->right_fork);
		}
		else
		{
    		pthread_mutex_unlock(philo->right_fork);
    		pthread_mutex_unlock(philo->left_fork);
		}
		print_state(philo, "is sleeping\n");
		precise_usleep(philo->shared->time_to_sleep);
		print_state(philo, "is thinking\n");
	}
	return (NULL);
}