#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		parse_input(&table, argv);
		// init_data(&table);
		// start_dinner(&table);
		// clean_programme();
	}
	else
	{
		exit_programme("5 or 6 values are needed.");
	}
}
