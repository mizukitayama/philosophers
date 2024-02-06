/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtayama <mtayama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:06:42 by mtayama           #+#    #+#             */
/*   Updated: 2024/02/06 20:55:26 by mtayama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*lone_philo(void	*arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	set_long(&(philo->philo_mutex), &(philo->last_meal_time),
		gettime(MILLISECOND, philo->table), philo->table);
	increase_long(&(philo->table->table_mutex),
		&(philo->table->threads_running_nbr), philo->table);
	write_status(TAKE_FIRST_FORK, philo);
	while (!simulation_finished(philo->table))
		ft_usleep(200, philo->table);
	return (NULL);
}

/* 
 * philo is not even,
 * 1. |eating||sleeping||   thinking   |💀
 * 2.         |eating||sleeping||eating| <- force to think
 * 3.                 |eating||sleeping|      after sleeping
 * 
 * 1. |eating|s|   think   |eating|
 * 2.        |eating|s|   think   |eating|
 * 3.               |eating|s|   think   |
 * time_to_think = time_to_eat * 2 - time_to_sleep
*/
void	think(t_philo *philo, bool is_pre_simulation)
{
	long	time_to_eat;
	long	time_to_sleep;
	long	time_to_think;

	if (!is_pre_simulation)
		write_status(THINKING, philo);
	if (philo->table->philo_nbr % 2 == 0)
		return ;
	time_to_eat = philo->table->time_to_eat;
	time_to_sleep = philo->table->time_to_sleep;
	time_to_think = time_to_eat * 2 - time_to_sleep;
	if (time_to_think < 0)
		time_to_think = 0;
	ft_usleep(time_to_think * 0.3, philo->table);
}

/*
 * 1. grabs the forks
 * 2. eat: write "eat", update last_meal_time, update meals_counter
 * 3. release the forks
*/
static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->first_fork->fork_mutex));
	write_status(TAKE_FIRST_FORK, philo);
	pthread_mutex_lock(&(philo->second_fork->fork_mutex));
	write_status(TAKE_SECOND_FORK, philo);
	set_long(&(philo->philo_mutex), &(philo->last_meal_time),
		gettime(MILLISECOND, philo->table), philo->table);
	philo->meals_counter++;
	write_status(EATING, philo);
	ft_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meals > 0
		&& philo->meals_counter == philo->table->nbr_limit_meals)
	{
		set_bool(&(philo->philo_mutex), &(philo->full), true, philo->table);
	}
	pthread_mutex_unlock(&(philo->first_fork->fork_mutex));
	pthread_mutex_unlock(&(philo->second_fork->fork_mutex));
}

/*
 * 1. waits all philos to start their simulation
 * 2. endless loop of eat, sleep, think
 * 
 * increase_long() -> synchro with monitor
 * 
*/
static void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&(philo->philo_mutex), &(philo->last_meal_time),
		gettime(MILLISECOND, philo->table), philo->table);
	increase_long(&(philo->table->table_mutex),
		&(philo->table->threads_running_nbr), philo->table);
	desynchronize_philo(philo);
	while (!simulation_finished(philo->table))
	{
		if (get_bool(&(philo->philo_mutex), &(philo->full), philo->table))
			break ;
		eat(philo);
		write_status(SLEEPING, philo);
		ft_usleep(philo->table->time_to_sleep, philo->table);
		think(philo, false);
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

	i = -1;
	if (table->nbr_limit_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
	{
		if (pthread_create(&(table->philos[0].thread_id), NULL,
				lone_philo, &(table->philos[0])) != 0)
			return ;
	}
	else
		while (++i < table->philo_nbr)
			if (pthread_create(&(table->philos[i].thread_id), NULL,
					dinner_simulation, &(table->philos[i])) != 0)
				return ;
	if (pthread_create(&(table->monitor), NULL, monitor, table) != 0)
		return ;
	table->start_simulation_time = gettime(MILLISECOND, table);
	set_bool(&(table->table_mutex), &(table->all_threads_ready), true, table);
	i = -1;
	while (++i < table->philo_nbr)
		pthread_join(table->philos[i].thread_id, NULL);
	set_bool(&(table->table_mutex), &(table->end_simulation), true, table);
	pthread_join(table->monitor, NULL);
}
