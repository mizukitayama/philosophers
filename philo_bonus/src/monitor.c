/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtayama <mtayama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:06:34 by mtayama           #+#    #+#             */
/*   Updated: 2024/05/11 17:58:59 by mtayama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;

	if (get_bool(philo->philo_sem, &(philo->full)))
		return (false);
	elapsed = gettime(MILLISECOND) - get_long(
			philo->philo_sem, &(philo->last_meal_time));
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
	while (!simulation_finished(table))
	{
		i = 0;
		while (i < table->philo_nbr && !simulation_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				set_bool(table->table_sem,
					&(table->end_simulation), true);
				write_status(DIED, table->philos + i);
			}
			i++;
		}
	}
	return (NULL);
}
