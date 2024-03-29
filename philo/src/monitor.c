/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtayama <mtayama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:06:34 by mtayama           #+#    #+#             */
/*   Updated: 2024/02/08 19:23:48 by mtayama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;

	if (get_bool(&(philo->philo_mutex), &(philo->full)))
		return (false);
	elapsed = gettime(MILLISECOND) - get_long(
			&(philo->philo_mutex), &(philo->last_meal_time));
	time_to_die = philo->table->time_to_die / 1000;
	if (elapsed > time_to_die)
		return (true);
	return (false);
}

void	*monitor(void *data)
{
	long	i;
	t_table	*table;

	table = (t_table *)data;
	while (!all_threads_running(&(table->table_mutex),
			&(table->threads_running_nbr), table->philo_nbr))
		;
	while (!simulation_finished(table))
	{
		i = 0;
		while (i < table->philo_nbr && !simulation_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				set_bool(&(table->table_mutex),
					&(table->end_simulation), true);
				write_status(DIED, table->philos + i);
			}
			i++;
		}
	}
	return (NULL);
}
