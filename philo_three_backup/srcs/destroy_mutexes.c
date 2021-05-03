#include "../incs/philo.h"

void
	*destroy_mutexes(t_info *info)
{
	int		idx;
	char	sem_name[255];

	(void)info;
    sem_unlink(SEM_FORK);
    sem_unlink(SEM_MSG);
    sem_unlink(SEM_SOMEONE_DEAD);
	idx = -1;
	while (++idx < info->num_of_philos)
	{
		memset(sem_name, 0, 255);
		gen_name_tag(sem_name, SEM_PHILO_EAT, idx);
		sem_unlink(sem_name);
	}
	return (NULL);
}
