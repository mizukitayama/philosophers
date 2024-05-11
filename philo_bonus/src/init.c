/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtayama <mtayama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:06:04 by mtayama           #+#    #+#             */
/*   Updated: 2024/05/11 18:22:55 by mtayama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		philo->philo_sem = sem_open("/philo", O_CREAT, 0644, 1);
		assign_forks(philo, table->forks, i);
		i++;
	}
}

int	init_data(t_table *table)
{
	long	i;

	i = 0;
	table->end_simulation = false;
	table->all_threads_ready = false;
	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
	if (table->philos == NULL)
		return (0);
	table->philos_malloc = true;
	table->table_sem = sem_open("/table", O_CREAT, 0644, 1);
	table->write_sem = sem_open("/write", O_CREAT, 0644, 1);
	table->forks = malloc(sizeof(t_fork) * table->philo_nbr);
	if (table->forks == NULL)
		return (0);
	table->forks_malloc = true;
	table->fork_sem = sem_open("/forks", O_CREAT, 0644, table->philo_nbr);
	init_philo(table);
	return (1);
}
