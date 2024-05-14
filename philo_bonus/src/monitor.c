/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtayama <mtayama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:06:34 by mtayama           #+#    #+#             */
/*   Updated: 2024/05/14 12:47:24 by mtayama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool philo_died(t_philo *philo)
{
	long elapsed;
	long time_to_die;

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
	t_philo	*philo;

	
	philo = (t_philo *)data;
	while (!simulation_finished(philo->table))
	{
		if (philo_died(philo))
		{
			set_bool(philo->table->table_sem,
					 &(philo->table->end_simulation), true);
			write_status(DIED, philo);
			exit(1);
		}
	}
	return (NULL);
}
