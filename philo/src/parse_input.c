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
/* checks negatives, degits, spaces, int max*/
{
	int				len;
	const char		*num;

	len = 0;
	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		exit_programme("Only positive values allowed.");
	if (!is_digit(*str))
		exit_programme("The input is not a digit.");
	num = str;
	while (is_digit(*str++))
		len++;
	if (len > 10)
		exit_programme("The value needs to be smaller than INT_MAX.");
	return (num);
}

static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	while (is_digit(*str))
		num = (num * 10) + (*str++ - '0');
	if (num > INT_MAX)
		exit_programme("The value needs to be smaller than INT_MAX.");
	return (num);
}

// number_of_philosophers
// time_to_die
// time_to_eat
// time_to_sleep
// [number_of_times_each_philosopher_must_eat]
void	parse_input(t_table *table, char **argv)
{
	table->philo_nbr = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1000;
	table->time_to_eat = ft_atol(argv[3]) * 1000;
	table->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (table->time_to_die < MIN_TIME
		|| table->time_to_eat < MIN_TIME
		|| table->time_to_sleep < MIN_TIME)
		exit_programme("Use a larger number for the timestamps.");
	if (argv[5])
		table->nbr_limit_meals = ft_atol(argv[5]);
	else
		table->nbr_limit_meals = -1;
}
