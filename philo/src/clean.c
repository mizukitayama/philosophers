/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtayama <mtayama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:04:26 by mtayama           #+#    #+#             */
/*   Updated: 2024/02/08 18:53:05 by mtayama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_programme(t_table *table)
{
	t_philo	*philo;
	long	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		philo = table->philos + i;
		pthread_mutex_destroy(&(philo->philo_mutex));
		i++;
	}
	pthread_mutex_destroy(&(table->write_mutex));
	pthread_mutex_destroy(&(table->table_mutex));
	free(table->forks);
	free(table->philos);
}
