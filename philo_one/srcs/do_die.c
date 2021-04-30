#include "../incs/philo.h"

void
	do_die(t_info *info, t_philo *philo)
{
	int	idx;

	if (info->program_finished)
		return ;
	show_message(philo, STATUS_DIE);
	idx = -1;
#if 1
	while (++idx < info->num_of_philos)
	{
		if (info->philos[idx].eat_finished)
			continue ;
		pthread_mutex_unlock(&info->philos[idx].eat_mutex);
	}
#endif
	pthread_mutex_unlock(&(info->someone_dead_mutex));
	info->program_finished = 1;
}
