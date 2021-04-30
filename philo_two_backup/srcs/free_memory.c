#include "../incs/philo.h"

void
	free_memory(t_info *info)
{
	if (info->philos != NULL)
	{
		free(info->philos);
		info->philos = NULL;
	}
}
