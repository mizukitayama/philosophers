#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, size_t pos)
{
	long	philo_nbr;
}

static void	philos_init(t_table *table)
{
	long	i;
	t_philo	*philo;

	i = 0;
	while (i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->meals_counter = 0;
		philo->full = false;
		philo->table = table;
		assign_forks(philo, table->forks, i);
	}
}

void	init_data(t_table *table)
{
	long	i;

	i = 0;
	table->end_simulation = false;
	table->philos = (t_philo *)secure_malloc(sizeof(t_philo) * table->philo_nbr);
	table->forks = (t_fork *)secure_malloc(sizeof(t_fork) * table->philo_nbr);
	while (i < table->philo_nbr)
	{
		mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
		i++;
	}

	philos_init(table);
}
