#include "philo.h"

static void free_table(t_table *table)
{
	if (table->forks_malloc == true)
		free(table->forks);
	if (table->philos_malloc == true)
		free(table->philos);
}

void	exit_programme(char *message, t_table *table_to_free)
{
	if (table_to_free != NULL)
		free_table(table_to_free);
	printf(R_ERR"%s\n"RST, message);
	exit(EXIT_FAILURE);
}

void	*safe_malloc(size_t bytes, t_table *table_to_free)
{
	void	*rt;

	rt = malloc(bytes);
	if (rt == NULL)
		exit_programme("Error in allocating memory.", table_to_free);
	return (rt);
}

long	gettime(t_time_code time_code, t_table *table_to_free)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		exit_programme("Gettimeofday has failed.", table_to_free);
	if (time_code == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1000000));
	else if (time_code == MILLISECOND)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else if (time_code == MICROSECOND)
		return ((tv.tv_sec * 1000000) + tv.tv_usec);
	exit_programme("Wrong input of time code.", table_to_free);
	return (0);
}

/*
 * usleep() to reduce CPU usage,
 * refine last microsec with spinlock
*/
void	ft_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = gettime(MICROSECOND, table);
	while (gettime(MICROSECOND, table) - start < usec)
	{
		if (simulation_finished(table))
			break ;
		elapsed = gettime(MICROSECOND, table) - start;
		remaining = usec - elapsed;
		if (remaining > 1000)
			usleep(remaining / 2);
		else
		// SPINLOCK
			while (gettime(MICROSECOND, table) - start < usec)
				;
	}
}
