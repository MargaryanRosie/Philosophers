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