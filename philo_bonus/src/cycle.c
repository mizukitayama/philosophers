/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtayama <mtayama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 20:48:12 by mtayama           #+#    #+#             */
/*   Updated: 2024/05/14 20:50:34 by mtayama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*lone_philo(void	*arg)
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

void	*dinner_simulation(void *data)
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
