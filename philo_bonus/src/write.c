/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtayama <mtayama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:06:51 by mtayama           #+#    #+#             */
/*   Updated: 2024/05/14 20:57:22 by mtayama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
 * [time_ms] [philo_id] [action]
 */
void	write_status(t_philo_status status, t_philo *philo)
{
	long	elapsed;

	elapsed = gettime(MILLISECOND) - philo->table->start_simulation_time;
	if (get_bool(philo->philo_sem, &(philo->full)))
		return ;
	sem_wait(philo->table->write_sem);
	if (status == DIED)
	{
		printf(B_TIME "%-7ld" G_DIED "%ld died\n" RST, elapsed, philo->id);
		return ;
	}
	if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK))
		printf(B_TIME "%-7ld" RST "%ld has taken a fork\n", elapsed,
			philo->id);
	else if (status == EATING)
		printf(B_TIME "%-7ld" B_EATING "%ld is eating\n" RST, elapsed,
			philo->id);
	else if (status == SLEEPING)
		printf(B_TIME "%-7ld" RST "%ld is sleeping\n", elapsed, philo->id);
	else if (status == THINKING)
		printf(B_TIME "%-7ld" RST "%ld is thinking\n", elapsed, philo->id);
	sem_post(philo->table->write_sem);
}
