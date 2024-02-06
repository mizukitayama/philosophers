/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_setter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtayama <mtayama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:04:45 by mtayama           #+#    #+#             */
/*   Updated: 2024/02/06 20:36:34 by mtayama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/* lock mutex to operate safely */

void	set_bool(t_mtx *mutex, bool *dest, bool value, t_table *table)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

bool	get_bool(t_mtx *mutex, bool *value, t_table *table)
{
	bool	rt;

	pthread_mutex_lock(mutex);
	rt = *value;
	pthread_mutex_unlock(mutex);
	return (rt);
}

void	set_long(t_mtx *mutex, long *dest, long value, t_table *table)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

long	get_long(t_mtx *mutex, long *value, t_table *table)
{
	long	rt;

	pthread_mutex_lock(mutex);
	rt = *value;
	pthread_mutex_unlock(mutex);
	return (rt);
}

bool	simulation_finished(t_table *table)
{
	return (get_bool(&(table->table_mutex), &(table->end_simulation), table));
}
