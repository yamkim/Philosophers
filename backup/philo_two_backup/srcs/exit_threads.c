#include "../incs/philo.h"

void
	*exit_threads(t_info *info)
{
	(void)info;
    sem_unlink(SEM_FORK);
    sem_unlink(SEM_INFO);
	return (NULL);
}

