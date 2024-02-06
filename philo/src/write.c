/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtayama <mtayama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:06:51 by mtayama           #+#    #+#             */
/*   Updated: 2024/02/06 20:48:35 by mtayama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * [time_ms] [philo_id] [action]
*/
void	write_status(t_philo_status status, t_philo *philo)
{
	long	elapsed;

	elapsed = gettime(MILLISECOND, philo->table)
		- philo->table->start_simulation_time;
	if (get_bool(&(philo->philo_mutex), &(philo->full), philo->table))
		return ;
	pthread_mutex_lock(&(philo->table->write_mutex));
	if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
		&& !simulation_finished(philo->table))
		printf(B_TIME"%-7ld"RST"%ld has taken a fork\n", elapsed, philo->id);
	else if (status == EATING && !simulation_finished(philo->table))
		printf(B_TIME"%-7ld"B_EATING"%ld is eating\n"RST, elapsed, philo->id);
	else if (status == SLEEPING && !simulation_finished(philo->table))
		printf(B_TIME"%-7ld"RST"%ld is sleeping\n", elapsed, philo->id);
	else if (status == THINKING && !simulation_finished(philo->table))
		printf(B_TIME"%-7ld"RST"%ld is thinking\n", elapsed, philo->id);
	else if (status == DIED)
		printf(B_TIME"%-7ld"G_DIED"%ld died\n"RST, elapsed, philo->id);
	pthread_mutex_unlock(&(philo->table->write_mutex));
}
