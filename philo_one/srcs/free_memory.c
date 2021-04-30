#include "../incs/philo.h"

void
	free_memory(t_info *info)
{
	if (info->fork_mutexes != NULL)
	{
		free(info->fork_mutexes);
		info->fork_mutexes = NULL;
	}
	if (info->philos != NULL)
	{
		free(info->philos);
		info->philos = NULL;
	}
}
