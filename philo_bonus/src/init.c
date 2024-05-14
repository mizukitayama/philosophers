/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtayama <mtayama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:06:04 by mtayama           #+#    #+#             */
/*   Updated: 2024/05/14 13:43:32 by mtayama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	init_philo(t_table *table)
/* i == position in table */
{
	long	i;
	t_philo	*philo;

	i = 0;
	sem_unlink("/philo");
	while (i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->table = table;
		philo->philo_sem = sem_open("/philo", O_CREAT, 0644, 1);
		i++;
	}
}

int	init_data(t_table *table)
{
	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
	if (table->philos == NULL)
		return (0);
	table->philos_malloc = true;
	sem_unlink("/write");
	sem_unlink("/table");
	sem_unlink("/forks");
	table->write_sem = sem_open("/write", O_CREAT, 0644, 1);
	table->table_sem = sem_open("/table", O_CREAT, 0644, 1);
	table->fork_sem = sem_open("/forks", O_CREAT, 0644, table->philo_nbr);
	init_philo(table);
	return (1);
}
