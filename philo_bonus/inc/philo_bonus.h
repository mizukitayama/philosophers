/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtayama <mtayama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:01:20 by mtayama           #+#    #+#             */
/*   Updated: 2024/05/11 18:39:28 by mtayama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>
#include <semaphore.h>
# include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

# define MIN_TIME	80000

# define RST		"\033[0m"
# define R_ERR		"\033[1;31m"
# define B_TIME		"\033[1;32m"
# define Y_ERR_MSG	"\033[1;33m"
# define B_EATING	"\033[1;34m"
# define G_DIED		"\033[1;35m" // Magenta

/* code for gettime */
typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}	t_time_code;

/* code for status of philo */
typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}	t_philo_status;

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

typedef struct s_fork
{
	t_mtx		fork_mutex;
	long		fork_id;
}	t_fork;

typedef struct s_philo
{
	long			id;
	long			meals_counter;
	bool			full;
	long			last_meal_time;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_t		thread_id;
	t_table			*table;
	t_mtx			philo_mutex;
	sem_t			*philo_sem;
	pid_t			pid;
}	t_philo;

struct s_table
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nbr_limit_meals;
	long		start_simulation_time;
	bool		end_simulation;
	bool		all_threads_ready;
	long		threads_running_nbr;
	t_fork		*forks;
	bool		forks_malloc;
	t_philo		*philos;
	bool		philos_malloc;
	t_mtx		table_mutex;
	t_mtx		write_mutex;
	pthread_t	monitor;
	sem_t		*fork_sem;
	sem_t		*write_sem;
	sem_t		*table_sem;
};

/* parse input*/
int		parse_input(t_table *table, char **argv);

/* init data */
int		init_data(t_table *table);

/* dinner simulation */
void	start_dinner(t_table *table);
void	think(t_philo *philo, bool is_pre_simulation);

/* utils */
void	free_programme(char *message, t_table *table);
long	gettime(t_time_code time_code);
void	ft_usleep(long usec, t_table *table);
void	*safe_malloc(size_t bytes, t_table *table);

/* write */
void	write_status(t_philo_status status, t_philo *philo);

/* getters and setters */
void	set_bool(sem_t *sem, bool *dest, bool value);
bool	get_bool(sem_t *sem, bool *value);
void	set_long(sem_t *sem, long *dest, long value);
long	get_long(sem_t *sem, long *value);
bool	simulation_finished(t_table *table);

/* synchronous functions */
void	wait_all_threads(t_table *table);
void	increase_long(sem_t *sem, long *value);
bool	all_threads_running(sem_t *sem, long *threads, long philo_nbr);
void	desynchronize_philo(t_philo *philo);

/* monitor */
void	*monitor(void *data);
bool	philo_died(t_philo *philo);

/* clean */
void	clean_programme(t_table *table);

#endif
