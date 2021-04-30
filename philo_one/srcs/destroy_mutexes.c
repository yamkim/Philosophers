#include "../incs/philo.h"

void
	*destroy_mutexes(t_info *info)
{
	int		idx;

	idx = -1;
	while (++idx < info->num_of_philos)
		pthread_mutex_destroy(&(info->fork_mutexes[idx]));
#if 1
	idx = -1;
	while (++idx < info->num_of_philos)
		pthread_mutex_destroy(&(info->philos[idx].eat_mutex));
#endif
	pthread_mutex_destroy(&(info->msg_mutex));
	pthread_mutex_destroy(&(info->someone_dead_mutex));
	return (NULL);
}

