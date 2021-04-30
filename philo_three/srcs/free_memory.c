#include "../incs/philo.h"

void
	free_memory(t_info *info)
{
	free(info->philos);
}
