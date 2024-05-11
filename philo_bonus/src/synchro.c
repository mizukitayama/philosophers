/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtayama <mtayama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:06:45 by mtayama           #+#    #+#             */
/*   Updated: 2024/05/11 19:18:57 by mtayama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_all_threads(t_table *table)
{
	while (!get_bool(table->table_sem, &(table->all_threads_ready)))
		;
}

bool	all_threads_running(sem_t *sem, long *threads, long philo_nbr)
{
	bool	rt;

	rt = false;
	sem_wait(sem);
	if (*threads == philo_nbr)
		rt = true;
	sem_post(sem);
	return (rt);
}

void	increase_long(sem_t *sem, long *value)
{
	sem_wait(sem);
	(*value)++;
	sem_post(sem);
}

/* 
 * when time_to_eat <= time_to_sleep
 * 1. |eating||sleeping||   thinking   |💀
 * 2.         |eating||sleeping||eating|
 * 3.                 |eating||sleeping|
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
