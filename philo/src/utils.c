#include "philo.h"

void	exit_programme(char *message)
{
	printf(R_ERR"%s\n"RST, message);
	exit(EXIT_FAILURE);
}

void	*safe_malloc(size_t bytes)
{
	void	*rt;

	rt = malloc(bytes);
	if (rt == NULL)
		exit_programme("Error in allocating memory.");
	return (rt);
}

/*

*/
void	*safe_mutex_handle()
{
}
