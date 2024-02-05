#include "philo.h"
/* lock mutex to operate safely */

void	set_bool(t_mtx *mutex, bool *dest, bool value, t_table *table)
{
	safe_mutex_handle(mutex, LOCK, table);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK, table);
}

bool	get_bool(t_mtx *mutex, bool *value, t_table *table)
{
	bool rt;

	safe_mutex_handle(mutex, LOCK, table);
	rt = *value;
	safe_mutex_handle(mutex, UNLOCK, table);
	return (rt);
}

void	set_long(t_mtx *mutex, long *dest, long value, t_table *table)
{
	safe_mutex_handle(mutex, LOCK, table);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK, table);
}

long	get_long(t_mtx *mutex, long *value, t_table *table)
{
	long rt;

	safe_mutex_handle(mutex, LOCK, table);
	rt = *value;
	safe_mutex_handle(mutex, UNLOCK, table);
	return (rt);
}

bool	simulation_finished(t_table *table)
{
	return (get_bool(&(table->table_mutex), &(table->end_simulation), table));
}
