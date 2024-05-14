/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_setter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtayama <mtayama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:04:45 by mtayama           #+#    #+#             */
/*   Updated: 2024/05/14 13:40:04 by mtayama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	set_bool(sem_t *sem, bool *dest, bool value)
{
	sem_wait(sem);
	*dest = value;
	sem_post(sem);
}

bool	get_bool(sem_t *sem, bool *value)
{
	bool	rt;

	sem_wait(sem);
	rt = *value;
	sem_post(sem);
	return (rt);
}

void	set_long(sem_t *sem, long *dest, long value)
{
	sem_wait(sem);
	*dest = value;
	sem_post(sem);
}

long	get_long(sem_t *sem, long *value)
{
	long	rt;

	sem_wait(sem);
	rt = *value;
	sem_post(sem);
	return (rt);
}

