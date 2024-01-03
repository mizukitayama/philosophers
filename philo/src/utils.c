#include "philo.h"

void	*secure_malloc(size_t size)
{
	void	*allocated;

	allocated = malloc(size);
	if (allocated == NULL)
		exit_programme("Error in allocating memory.");
	return (allocated);
}

void	exit_programme(char *message)
{
	printf("%s\n", message);
	exit(EXIT_FAILURE);
}
