/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtayama <mtayama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:04:26 by mtayama           #+#    #+#             */
/*   Updated: 2024/05/14 12:20:10 by mtayama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	clean_programme(t_table *table)
{
	t_philo	*philo;
	long	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		philo = table->philos + i;
		sem_unlink("/philo");
		sem_close(philo->philo_sem);
		i++;
	}
	sem_unlink("/write");
	sem_close(table->write_sem);
	sem_unlink("/table");
	sem_close(table->table_sem);
	free(table->forks);
	free(table->philos);
}
