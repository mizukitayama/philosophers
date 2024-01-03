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

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

typedef struct s_fork
{
	t_mtx	fork;
	size_t		fork_id;
}	t_fork;

typedef struct s_philo
{
	size_t			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time;
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread_id;
	t_table		*table;
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
	t_fork	*forks;
	t_philo	*philos;
};

void	*secure_malloc(size_t size);
void	exit_programme(char *message);
void	parse_input(t_table *table, char **argv);
void	init_data(t_table *table);
void	thread_handle(pthread_t *thread, void*(*foo)(void *),
	void *data, t_opcode opcode);
void	mutex_handle(t_mtx *mutex, t_opcode opcode);
#endif
