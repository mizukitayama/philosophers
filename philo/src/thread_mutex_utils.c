#include "philo.h"

static void	handle_mutex_error(t_opcode opcode, int status)
{
	if (status == 0)
		return ;
	if (status == EINVAL && opcode == INIT)
		exit_programme("The value specified by attr is invalid.");
	else if (status == EINVAL
		&& (opcode == LOCK || opcode == UNLOCK || opcode == DESTROY))
		exit_programme("The value specified by mutex is invalid.");
	else if (status == EDEADLK)
		exit_programme("A deadlock would occur if the thread blocked waiting for mutex.");
	else if (status == EPERM)
		exit_programme("The current thread does not hold a lock on mutex.");
	else if (status == ENOMEM)
		exit_programme("The process cannot allocate enough momery to create another mutex.");
	else if (status == EBUSY)
		exit_programme("Mutex locked.");
}

void	mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		handle_mutex_error(opcode, pthread_mutex_lock(mutex));
	else if (opcode == UNLOCK)
		handle_mutex_error(opcode, pthread_mutex_unlock(mutex));
	else if (opcode == INIT)
		handle_mutex_error(opcode, pthread_mutex_init(mutex, NULL));
	else if (opcode == DESTROY)
		handle_mutex_error(opcode, pthread_mutex_destroy(mutex));
	else
		exit_programme("Invalid opcode for mutex_handle.");		
}

static void	handle_thread_error(t_opcode opcode, int status)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		exit_programme("No resources to create another thread.");
	else if (status == EPERM)
		exit_programme("The caller does not have appropriate permission.");
	else if (status == EINVAL && opcode == CREATE)
		exit_programme("The value specified by attr is invalid.");
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		exit_programme("The value specified by thread is not joinable.");
	else if (status == ESRCH)
		exit_programme("No thread could be found corresponding to that specified"
			"by the given thread ID, thread.");
	else if (status == EDEADLK)
		exit_programme("A deadlock was detected or the value of thread specifies"
			"the calling thread.");
}

void	thread_handle(pthread_t *thread, void*(*foo)(void *),
	void *data, t_opcode opcode)
{
	if (opcode == CREATE)
		handle_thread_error(opcode, pthread_create(thread, NULL, foo, data));
	else if (opcode == JOIN)
		handle_thread_error(opcode, pthread_join(*thread, NULL));
	else if (opcode == DETACH)
		handle_thread_error(opcode, pthread_detach(*thread));
	else
		exit_programme("Invalid opcode for thread_handle.");
}
