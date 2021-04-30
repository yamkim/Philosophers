#include "../incs/philo.h"

int
	do_die(t_info *info, t_philo *philo)
{
	philo->status = STATUS_DIE;
	if (show_message(philo, STATUS_DIE))
		return (ERR_SEM_DO);
	info->someone_dead = 1;
	return (0);
}
