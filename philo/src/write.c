#include "philo.h"

/*
 * [time_ms] [philo_id] [action]
*/
void	write_status(t_philo_status status, t_philo *philo)
{
	long	elapsed;

	elapsed = gettime(MILLISECOND, philo->table) - philo->table->start_simulation_time;
	if (get_bool(&(philo->philo_mutex), &(philo->full), philo->table))
		return ;
	safe_mutex_handle(&(philo->table->write_mutex), LOCK, philo->table);
	if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
			&& !simulation_finished(philo->table))
		printf(G_TIME"%-6ld"RST"%ld has taken a fork\n", elapsed, philo->id);
	else if (status == EATING && !simulation_finished(philo->table))
		printf(G_TIME"%-6ld"RST"%ld is eating\n", elapsed, philo->id);
	else if (status == SLEEPING && !simulation_finished(philo->table))
		printf(G_TIME"%-6ld"RST"%ld is sleeping\n", elapsed, philo->id);
	else if (status == THINKING && !simulation_finished(philo->table))
		printf(G_TIME"%-6ld"RST"%ld is thinking\n", elapsed, philo->id);
	else if (status == DIED)
		printf(G_TIME"%-6ld"RST"%ld is died\n", elapsed, philo->id);
	safe_mutex_handle(&(philo->table->write_mutex), UNLOCK, philo->table);
}
