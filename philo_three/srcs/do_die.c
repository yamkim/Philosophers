#include "../incs/philo.h"

int
	do_die(t_info *info, t_philo *philo)
{
	int	idx;

	if (sem_post(info->someone_dead_mutex))
		return (ERR_SEM_DO);
	show_message(philo, STATUS_DIE);
	idx = -1;
#if 1
	while (++idx < info->num_of_philos)
	{
		if (sem_post(info->philos[idx].eat_mutex))
			return (ERR_SEM_DO);
	}
#endif
	return (0);
}
