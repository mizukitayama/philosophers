/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtayama <mtayama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:06:45 by mtayama           #+#    #+#             */
/*   Updated: 2024/05/14 13:42:39 by mtayama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
			ft_usleep(30000);
	}
	else
	{
		if (philo->id % 2 != 0)
			think(philo, true);
	}
}
