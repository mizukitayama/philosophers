#include "philo.h"

/* 
 * philos at even position take fork :
 * first: on their right side
 * second: on their left side
 * 
 * philos at odd position take fork :
 * first: on their left side
 * second: on their right side
*/
static void	assign_forks(t_philo *philo, t_fork *forks, size_t position)

{
	long	philo_nbr;

	philo_nbr = philo->table->philo_nbr;

	if (philo->id % 2 == 0)
	{
		philo->first_fork = &(forks[position]);
		philo->second_fork = &(forks[(position + 1) % philo_nbr]);
	}
	else
	{
		philo->second_fork = &(forks[position]);
		philo->first_fork = &(forks[(position + 1) % philo_nbr]);
	}
}

static void	init_philo(t_table *table)
/* i == position in table */
{
	long	i;
	t_philo	*philo;

	i = 0;
	while (i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->table = table;
		safe_mutex_handle(&(philo->philo_mutex), INIT, table);
		assign_forks(philo, table->forks, i);
		i++;
	}
}

void	init_data(t_table *table)
{
	long	i;

	i = 0;
	table->end_simulation = false;
	table->all_threads_ready = false;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr, NULL);
	table->philos_malloc = true;
	safe_mutex_handle(&(table->table_mutex), INIT, table);
	safe_mutex_handle(&(table->write_mutex), INIT, table);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr, table);
	table->forks_malloc = true;
	while(i < table->philo_nbr)
	{
		safe_mutex_handle(&(table->forks[i].fork_mutex), INIT, table);
		table->forks[i].fork_id = i;
		i++;
	}
	init_philo(table);
}
