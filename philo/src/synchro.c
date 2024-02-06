/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtayama <mtayama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:06:45 by mtayama           #+#    #+#             */
/*   Updated: 2024/02/06 20:46:19 by mtayama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&(table->table_mutex), &(table->all_threads_ready), table))
		;
}

bool	all_threads_running(t_mtx *mutex, long *threads,
	long philo_nbr, t_table *table)
{
	bool	rt;

	rt = false;
	pthread_mutex_lock(mutex);
	if (*threads == philo_nbr)
		rt = true;
	pthread_mutex_unlock(mutex);
	return (rt);
}

void	increase_long(t_mtx *mutex, long *value, t_table *table)
{
	pthread_mutex_lock(mutex);
	(*value)++;
	pthread_mutex_unlock(mutex);
}

/* 
 * when time_to_eat <= time_to_sleep
 * 1. |eating||sleeping||   thinking   |💀
 * 2.         |eating||sleeping||eating| <- force to think
 * 3.                 |eating||sleeping|      after sleeping
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
