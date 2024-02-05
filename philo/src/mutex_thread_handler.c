#include "philo.h"

/* MUTEX */
static void	handle_mutex_errors(int status, t_opcode opcode, t_table *table_to_free)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (opcode == DESTROY
			|| opcode == LOCK || opcode == UNLOCK))
		exit_programme("The value specified by mutex is invalid.\n", table_to_free);
	else if (status == EINVAL && opcode == INIT)
		exit_programme("The value specified by attr is invalid.", table_to_free);
	else if (status == EDEADLK)
		exit_programme("A deadlock would occur if the thread"
			"blocked waiting for mutex.", table_to_free);
	else if (status == EPERM)
		exit_programme("The current thread does not hold a lock on mutex.", table_to_free);
	else if (status == ENOMEM)
		exit_programme("The process cannot allocate enough"
			"memory to create another mutex.", table_to_free);
	else if (status == EBUSY)
		exit_programme("Mutex is locked.", table_to_free);
}

void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode, t_table *table_to_free)
{
	if (opcode == LOCK)
		handle_mutex_errors(pthread_mutex_lock(mutex), opcode, table_to_free);
	else if (opcode == UNLOCK)
		handle_mutex_errors(pthread_mutex_unlock(mutex), opcode, table_to_free);
	else if (opcode == INIT)
		handle_mutex_errors(pthread_mutex_init(mutex, NULL), opcode, table_to_free);
	else if (opcode == DESTROY)
		handle_mutex_errors(pthread_mutex_destroy(mutex), opcode, table_to_free);
	else
		exit_programme("Error in mutex opcode", table_to_free);
}

/* THREADS*/
static void	handle_thread_errors(int status, t_opcode opcode, t_table *table_to_free)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		exit_programme("No resources to create another thread.", table_to_free);
	else if (status == EPERM)
		exit_programme("The caller does not have appropriate permission.", table_to_free);
	else if (status == EINVAL && opcode == CREATE)
		exit_programme("The value specified by attre is invalid.", table_to_free);
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		exit_programme("The value specified by thread is not joinable.", table_to_free);
	else if (status == ESRCH)
		exit_programme("No thread could be found corresponding to that"
			"specified by the given thread ID, thread.", table_to_free);
	else if (status == EDEADLK)
		exit_programme("A deadlock was detected or the value of"
			"thread specifies the calling thread.", table_to_free);
}

void	safe_thread_handle(pthread_t *thread, void *(foo)(void *),
		void *data, t_opcode opcode, t_table *table_to_free)
{
	if (opcode == CREATE)
		handle_thread_errors(pthread_create(thread, NULL, foo, data), opcode, table_to_free);
	else if (opcode == JOIN)
		handle_thread_errors(pthread_join(*thread, NULL), opcode, table_to_free);
	else if (opcode == DETACH)
		handle_thread_errors(pthread_detach(*thread), opcode, table_to_free);
	else
		exit_programme("Error in thread opcode.", table_to_free);
}
