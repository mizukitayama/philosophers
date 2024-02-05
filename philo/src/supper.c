#include "philo.h"

void	*lone_philo(void	*arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	set_long(&(philo->philo_mutex), &(philo->last_meal_time), gettime(MILLISECOND, philo->table), philo->table);
	increase_long(&(philo->table->table_mutex), &(philo->table->threads_running_nbr), philo->table);
	write_status(TAKE_FIRST_FORK, philo);
	while (!simulation_finished(philo->table))
		usleep(100);
	return (NULL);
}

static void	think(t_philo *philo)
{
	write_status(THINKING, philo);
}

/*
 * 1. grabs the forks
 * 2. eat: write "eat", update last_meal_time, update meals_counter
 * 3. release the forks
*/
static void	eat(t_philo *philo)
{
	safe_mutex_handle(&(philo->first_fork->fork_mutex), LOCK, philo->table);
	write_status(TAKE_FIRST_FORK, philo);
	safe_mutex_handle(&(philo->second_fork->fork_mutex), LOCK, philo->table);
	write_status(TAKE_SECOND_FORK, philo);
	set_long(&(philo->philo_mutex), &(philo->last_meal_time), gettime(MILLISECOND, philo->table), philo->table);
	philo->meals_counter++;
	write_status(EATING, philo);
	ft_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meals > 0 && philo->meals_counter == philo->table->nbr_limit_meals)
		set_bool(&(philo->philo_mutex), &(philo->full), true, philo->table);
	safe_mutex_handle(&(philo->first_fork->fork_mutex), UNLOCK, philo->table);
	safe_mutex_handle(&(philo->second_fork->fork_mutex), UNLOCK, philo->table);
}

/*
 * 1. waits all philos to start their simulation
 * 2. endless loop of eat, sleep, think
*/
static void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&(philo->philo_mutex), &(philo->last_meal_time), gettime(MILLISECOND, philo->table), philo->table);
	increase_long(&(philo->table->table_mutex), &(philo->table->threads_running_nbr), philo->table);

	while (!simulation_finished(philo->table))
	{
		if (philo->full)
			break;
		eat(philo);
		write_status(SLEEPING, philo);
		ft_usleep(philo->table->time_to_sleep, philo->table);
		think(philo);
	}
	return (NULL);
}

/*
 * 1.  if must_eat == 0, return 0
 * 1.1 if num_of_philo == 1, specific func
 * 2. creates all threads, all philos
 * 3. creates a monitor thread
 * 4. synchronize the beggining of the simulation
 * 5. JOIN every philo
*/
void	start_dinner(t_table *table)
{
	long	i;

	i = 0;
	if (table->nbr_limit_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
		safe_thread_handle(&(table->philos[0].thread_id), lone_philo, &(table->philos[0]), CREATE, table);
	else
	{
		while (i < table->philo_nbr)
		{
			safe_thread_handle(&(table->philos[i].thread_id), dinner_simulation,
				&(table->philos[i]), CREATE, table);
			i++;
		}
	}
	safe_thread_handle(&(table->monitor), monitor, table, CREATE, table);
	table->start_simulation_time = gettime(MILLISECOND, table);
	set_bool(&(table->table_mutex), &(table->all_threads_ready), true, table);
	i = 0;
	while (i < table->philo_nbr)
	{
		safe_thread_handle(&(table->philos[i].thread_id), NULL, NULL, JOIN, table);
		i++;
	}
	set_bool(&(table->table_mutex), &(table->end_simulation), true, table);
	safe_thread_handle(&(table->monitor), NULL, NULL, JOIN, table);
}
