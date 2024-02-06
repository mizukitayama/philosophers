#include "philo.h"

void	clean_programme(t_table *table)
{
	t_philo	*philo;
	long		i;

	i = 0;
	while (i < table->philo_nbr)
	{
		philo = table->philos + i;
		safe_mutex_handle(&(philo->philo_mutex), DESTROY, table);
		i++;
	}
	safe_mutex_handle(&(table->write_mutex), DESTROY, table);
	safe_mutex_handle(&(table->table_mutex), DESTROY, table);
	free(table->forks);
	free(table->philos);
}