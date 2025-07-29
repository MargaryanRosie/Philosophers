#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <pthread.h>

struct s_shared;         //so that the compiler knows that this struct exists

typedef struct s_philosopher
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_shared		*shared;       //we take the pointers to the mutexes to avoid fork duplication
}	t_philosopher;

typedef struct s_shared
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	pthread_mutex_t	*forks;         //array of forks
	t_philosopher	*philosophers;
}	t_shared;

int	ft_atoi(char *str);
int	init_rules(char *argv[], t_rules *rules);

#endif