/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtayama <mtayama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:06:42 by mtayama           #+#    #+#             */
/*   Updated: 2024/05/14 13:45:15 by mtayama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*lone_philo(void	*arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	set_long(philo->philo_sem, &(philo->last_meal_time),
		gettime(MILLISECOND));
	write_status(TAKE_FIRST_FORK, philo);
	while (!philo_died(philo))
		ft_usleep(10);
	write_status(DIED, philo);
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
	ft_usleep(time_to_think * 0.3);
}

/*
 * 1. grabs the forks
 * 2. eat: write "eat", update last_meal_time, update meals_counter
 * 3. release the forks
*/
static void	eat(t_philo *philo)
{
	sem_wait(philo->table->fork_sem);
	write_status(TAKE_FIRST_FORK, philo);
	sem_wait(philo->table->fork_sem);
	write_status(TAKE_SECOND_FORK, philo);
	set_long(philo->philo_sem, &(philo->last_meal_time),
		gettime(MILLISECOND));
	philo->meals_counter++;
	write_status(EATING, philo);
	ft_usleep(philo->table->time_to_eat);
	if (philo->table->nbr_limit_meals > 0
		&& philo->meals_counter == philo->table->nbr_limit_meals)
	{
		set_bool(philo->philo_sem, &(philo->full), true);
	}
	sem_post(philo->table->fork_sem);
	sem_post(philo->table->fork_sem);
}

static void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (gettime(MILLISECOND) < philo->table->start_simulation_time)
		;
	if (pthread_create(&(philo->monitor), NULL, monitor, philo) != 0)
		return (NULL);
	set_long(philo->philo_sem, &(philo->last_meal_time),
		gettime(MILLISECOND));
	desynchronize_philo(philo);
	while (1)
	{
		if (get_bool(philo->philo_sem, &(philo->full)))
			break ;
		eat(philo);
		write_status(SLEEPING, philo);
		ft_usleep(philo->table->time_to_sleep);
		think(philo, false);
	}
	return (NULL);
}

void	start_dinner(t_table *table)
{
	long	i;

	i = -1;
	if (table->nbr_limit_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
	{
		set_long(table->table_sem, &(table->start_simulation_time), gettime(MILLISECOND));
		lone_philo(&(table->philos[0]));
	}
	else
	{
		set_long(table->table_sem, &(table->start_simulation_time), gettime(MILLISECOND) + 1000);
		while (++i < table->philo_nbr) {
			set_long(table->philos[i].philo_sem, &(table->philos[i].last_meal_time), table->start_simulation_time);
			table->philos[i].pid = fork();
			if (table->philos[i].pid == 0) {
				dinner_simulation(&(table->philos[i]));
				exit(1);
			}
		}
		i = -1;
		waitpid(-1, NULL, WCONTINUED);
		while (++i < table->philo_nbr)
			kill(table->philos[i].pid, SIGINT);
	}
}
