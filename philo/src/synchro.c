#include "philo.h"

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&(table->table_mutex), &(table->all_threads_ready), table))
		;
}

bool	all_threads_running(t_mtx *mutex, long *threads, long philo_nbr, t_table *table)
{
	bool	rt;

	rt = false;
	safe_mutex_handle(mutex, LOCK, table);
	if (*threads == philo_nbr)
		rt = true;
	safe_mutex_handle(mutex, UNLOCK, table);
	return (rt);
}

void	increase_long(t_mtx *mutex, long *value, t_table *table)
{
	safe_mutex_handle(mutex, LOCK, table);
	(*value)++;
	safe_mutex_handle(mutex, UNLOCK, table);
}
