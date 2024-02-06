/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtayama <mtayama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:06:48 by mtayama           #+#    #+#             */
/*   Updated: 2024/02/06 19:57:46 by mtayama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_programme(char *message, t_table *table)
{
	if (table != NULL)
	{
		if (table->forks_malloc == true)
			free(table->forks);
		if (table->philos_malloc == true)
			free(table->philos);
	}
	printf(R_ERR"%s\n"RST, message);
}

void	*safe_malloc(size_t bytes, t_table *table)
{
	void	*rt;

	rt = malloc(bytes);
	if (rt == NULL)
	{
		exit_programme("Error in allocating memory.", table);
	}
	return (rt);
}

long	gettime(t_time_code time_code, t_table *table)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (time_code == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1000000));
	else if (time_code == MILLISECOND)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else if (time_code == MICROSECOND)
		return ((tv.tv_sec * 1000000) + tv.tv_usec);
	return (0);
}

/*
 * refine last microsec with spinlock
*/
void	ft_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = gettime(MICROSECOND, table);
	while (gettime(MICROSECOND, table) - start < usec)
	{
		if (simulation_finished(table))
			break ;
		elapsed = gettime(MICROSECOND, table) - start;
		remaining = usec - elapsed;
		if (remaining > 1000)
			usleep(remaining / 2);
		else
			while (gettime(MICROSECOND, table) - start < usec)
				;
	}
}
