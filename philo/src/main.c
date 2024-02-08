/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtayama <mtayama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:06:28 by mtayama           #+#    #+#             */
/*   Updated: 2024/02/08 19:45:25 by mtayama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		if (!parse_input(&table, argv))
			return (0);
		if (!init_data(&table))
			return (0);
		start_dinner(&table);
		clean_programme(&table);
		return (0);
	}
	else
	{
		free_programme("Error\n"Y_ERR_MSG"5 or 6 inputs needed.", NULL);
		return (0);
	}
}

// static void destructor() __attribute__((destructor));
// static void destructor() {
//     system("leaks -q philo");
// }