#	ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

# ifndef MIN_TIME
#  define MIN_TIME	60000
# endif

# define RST							"\033[0m"
# define R_ERR						"\033[1;31m"
# define G								"\033[1;32m"
# define Y_ERR_MSG				"\033[1;33m"
# define B								"\033[1;34m"
# define M								"\033[1;35m" // Magenta
# define C								"\033[1;36m" // Cyan

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;

typedef struct s_philo
{
	int			id;
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

void	exit_programme(char *message);
void	parse_input(t_table *table, char **argv);
void	*safe_malloc(size_t bytes);
#endif
