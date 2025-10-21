/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romargar <rosie.margaryan@mail.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:05:40 by romargar          #+#    #+#             */
/*   Updated: 2025/10/21 15:05:41 by romargar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_shared t_shared;         //so that the compiler knows that this struct exists

typedef struct s_philosopher
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_shared		*shared;       //we take the pointers to the mutexes to avoid fork duplication
	int				meals_eaten;
	long long		last_meal_time;
}	t_philosopher;

typedef struct s_shared
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	long long		start_time;
	pthread_mutex_t	*forks;         //array of forks
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	last_meal_mutex;
	t_philosopher	*philosophers;
	int				someone_died;
}	t_shared;

int			ft_atoi(char *str);
long long	get_time_in_milliseconds(void);
int			init_shared(char *argv[], int argc, t_shared *shared);
int			init_mutexes(t_shared *shared);
int			init_philosophers(t_shared *shared);
void	*death_monitor(void *arg);

void	*routine(void *arg);


#endif