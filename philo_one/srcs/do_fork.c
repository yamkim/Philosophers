#include "../incs/philo.h"

void
	take_fork(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&(info->fork_mutexes[philo->lfork]));
	show_message(philo, STATUS_FORK);

	pthread_mutex_lock(&(info->fork_mutexes[philo->rfork]));
	show_message(philo, STATUS_FORK);
}

void
	return_fork(t_info *info, t_philo *philo)
{
	pthread_mutex_unlock(&(info->fork_mutexes[philo->lfork]));
	pthread_mutex_unlock(&(info->fork_mutexes[philo->rfork]));
}
