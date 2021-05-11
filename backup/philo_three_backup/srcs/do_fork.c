#include "../incs/philo.h"

int
	take_fork(t_info *info, t_philo *philo)
{
	if (sem_wait(info->fork_mutexes))
		return (ERR_SEM_DO);
	if (show_message(philo, STATUS_FORK))
		return (ERR_SEM_DO);
	if (sem_wait(info->fork_mutexes))
		return (ERR_SEM_DO);
	if (show_message(philo, STATUS_FORK))
		return (ERR_SEM_DO);
	return (0);
}

int
	return_fork(t_info *info, t_philo *philo)
{
	(void)philo;
	if (sem_post(info->fork_mutexes))
		return (ERR_SEM_DO);
	if (sem_post(info->fork_mutexes))
		return (ERR_SEM_DO);
	return (0);
}
