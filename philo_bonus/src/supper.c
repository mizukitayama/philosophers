/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtayama <mtayama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:06:42 by mtayama           #+#    #+#             */
/*   Updated: 2024/05/14 21:18:35 by mtayama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
void	eat(t_philo *philo)
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

void	create_process(t_table *table)
{
	long	i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		set_long(table->philos[i].philo_sem, &(table->philos[i].last_meal_time),
			table->start_simulation_time);
		table->philos[i].pid = fork();
		if (table->philos[i].pid == 0)
		{
			dinner_simulation(&(table->philos[i]));
			exit(1);
		}
	}
	i = -1;
	waitpid(-1, NULL, WCONTINUED);
	while (++i < table->philo_nbr)
		kill(table->philos[i].pid, SIGINT);
}

void	start_dinner(t_table *table)
{
	if (table->nbr_limit_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
	{
		set_long(table->table_sem, &(table->start_simulation_time),
			gettime(MILLISECOND));
		lone_philo(&(table->philos[0]));
	}
	else
	{
		set_long(table->table_sem, &(table->start_simulation_time),
			gettime(MILLISECOND) + 1000);
		create_process(table);
	}
}
