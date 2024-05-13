/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtayama <mtayama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:04:26 by mtayama           #+#    #+#             */
/*   Updated: 2024/05/11 17:59:12 by mtayama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	clean_programme(t_table *table)
{
	// t_philo	*philo;
	long	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		// philo = table->philos + i;
		sem_unlink("/philo");
		i++;
	}
	sem_unlink("/write");
	sem_unlink("/table");
	free(table->forks);
	free(table->philos);
}
