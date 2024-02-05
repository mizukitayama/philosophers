#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		parse_input(&table, argv);
		init_data(&table);
		start_dinner(&table);
		clean_programme(&table);
	}
	else
	{
		exit_programme("Error\n"Y_ERR_MSG"5 or 6 inputs needed.", NULL);
	}
}

static void destructor() __attribute__((destructor));

static void destructor() {
    system("leaks -q philo");
}