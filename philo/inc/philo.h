#	ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

# ifndef MIN_TIME
#  define MIN_TIME	60000
# endif

# define RST							"\033[0m"
# define R_ERR						"\033[1;31m"
# define G_TIME						"\033[1;32m"
# define Y_ERR_MSG				"\033[1;33m"
# define B								"\033[1;34m"
# define M								"\033[1;35m" // Magenta
# define C								"\033[1;36m" // Cyan

/* opcode for mutex and thread */
typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;

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
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_table		*table;
	t_mtx			philo_mutex;
}	t_philo;

struct s_table
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nbr_limit_meals;
	long	start_simulation_time;
	bool	end_simulation;
	bool	all_threads_ready;
	long	threads_running_nbr;
	t_fork	*forks;
	bool		forks_malloc;
	t_philo	*philos;
	bool		philos_malloc;
	t_mtx			table_mutex;
	t_mtx			write_mutex;
	pthread_t	monitor;
};

/* parse input*/
void	parse_input(t_table *table, char **argv);

/* init data */
void	init_data(t_table *table);

/* dinner simulation */
void	start_dinner(t_table *table);

/* utils */
void	exit_programme(char *message, t_table *table);
void	*safe_malloc(size_t bytes, t_table *table_to_free);
long	gettime(t_time_code time_code, t_table *table_to_free);
void	ft_usleep(long usec, t_table *table);

/* write */
void	write_status(t_philo_status status, t_philo *philo);

/* mutex and thread handlers */
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode, t_table *table_to_free);
void	safe_thread_handle(pthread_t *thread, void *(foo)(void *),
			void *data, t_opcode opcode, t_table *table_to_free);

/* getters and setters */
void	set_bool(t_mtx *mutex, bool *dest, bool value, t_table *table);
bool	get_bool(t_mtx *mutex, bool *value, t_table *table);
void	set_long(t_mtx *mutex, long *dest, long value, t_table *table);
long	get_long(t_mtx *mutex, long *value, t_table *table);
bool	simulation_finished(t_table *table);

/* synchronous functions */
void	wait_all_threads(t_table *table);
void	increase_long(t_mtx *mutex, long *value, t_table *table);
bool	all_threads_running(t_mtx *mutex, long *threads, long philo_nbr, t_table *table);

/* monitor */
void	*monitor(void *data);

#endif
