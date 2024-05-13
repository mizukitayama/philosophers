/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtayama <mtayama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:06:39 by mtayama           #+#    #+#             */
/*   Updated: 2024/02/08 19:40:13 by mtayama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static const char	*valid_input(const char *str)
/* checks negatives, degits, spaces, int max */
{
	const char		*num;

	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	num = str;
	while (*str)
	{
		if (!is_digit(*str))
		{
			free_programme("Error\n"Y_ERR_MSG"The input is not a digit.", NULL);
			return (NULL);
		}
		str++;
	}
	return (num);
}

static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	if (str == NULL)
		return (-1);
	while (is_digit(*str))
		num = (num * 10) + (*str++ - '0');
	if (num > INT_MAX)
	{
		free_programme("Error\n"
			Y_ERR_MSG"The value needs to be smaller than INT_MAX.", NULL);
		return (-1);
	}
	return (num);
}

/*
 *	arguments:
 *	1 number_of_philosophers
 *	2 time_to_die
 *	3 time_to_eat
 *	4 time_to_sleep
 *	5 [number_of_times_each_philosopher_must_eat]
*/
int	parse_input(t_table *table, char **argv)
/* checks inputs and init data, converting time to miliseconds */
{
	table->philo_nbr = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1000;
	table->time_to_eat = ft_atol(argv[3]) * 1000;
	table->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (argv[5])
		table->nbr_limit_meals = ft_atol(argv[5]);
	else
		table->nbr_limit_meals = -2;
	if (table->philo_nbr == -1 || table->time_to_die == -1
		|| table->time_to_sleep == -1 || table->nbr_limit_meals == -1)
		return (0);
	if (table->time_to_die < MIN_TIME
		|| table->time_to_eat < MIN_TIME
		|| table->time_to_sleep < MIN_TIME)
	{
		free_programme("Error\n"
			Y_ERR_MSG"Use a larger number for the timestamps.", NULL);
		return (0);
	}
	return (1);
}
