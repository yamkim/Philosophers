#include "../incs/philo.h"

int
	do_eat(t_info *info, t_philo *philo)
{
	if (sem_wait(philo->mutex))
		return (ERR_SEM_DO);

	philo->status = STATUS_EAT;
	philo->beg_eat_time = get_cur_time();
	show_message(philo, STATUS_EAT);
	usleep(info->time_to_eat * MSEC2USEC);
	++(philo->eat_cnt);
	if (philo->eat_cnt == info->num_of_must_eat)
		info->finished_thread[philo->pos - 1] = 1;

	if (sem_post(philo->mutex))
		return (ERR_SEM_DO);
	return (0);
}
