/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romargar <rosie.margaryan@mail.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:05:48 by romargar          #+#    #+#             */
/*   Updated: 2025/10/21 15:05:49 by romargar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_digit_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(char *str)
{
	int		i;
	long	result;

	if (!str)
		return (-1);
	if (!is_digit_string(str))
	{
		write(2, "Error\nThe string contians invalid characters.", 45);
		return (-1);     // because in the case of 0, output 0 is valid
	}
	i = 0;
	result = 0;
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		if (result > INT_MAX)
		{
			write(2, "Error\nOverflow\n", 15);
			return (-1);
		}
		i++;
	}
	return ((int)result);
}

//header defines

// struct timeval {
//     time_t      tv_sec;   // whole seconds since 1970, time_t is typedef for long
//     suseconds_t tv_usec;  // microseconds (millionths of a second)
// };

long long	get_time_in_milliseconds(void)
{
	struct timeval	time_value;
	long long		time_in_milliseconds;

	gettimeofday(&time_value, NULL);    //fills the time values in struct
	time_in_milliseconds = (long long)(time_value.tv_sec
		* 1000 + time_value.tv_usec / 1000);
	return (time_in_milliseconds);
}
