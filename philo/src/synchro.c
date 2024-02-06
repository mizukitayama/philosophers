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

/* 
 * when time_to_eat <= time_to_sleep
 * 1. |eating||sleeping||   thinking   |💀
 * 2.         |eating||sleeping||eating| <- force to think
 * 3.                 |eating||sleeping|      after sleeping
 * 
 * 1.
 * 2.
 * 3.
*/
void	desynchronize_philo(t_philo *philo)
{
	if (philo->table->philo_nbr % 2 == 0)
	{
		if (philo->id % 2 == 0)
			ft_usleep(30000, philo->table);
	}
	else 
	{
		if (philo->id % 2 != 0)
			think(philo, true);
	}
}
