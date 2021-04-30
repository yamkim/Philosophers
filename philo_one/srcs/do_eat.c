#include "../incs/philo.h"

void
	do_eat(t_info *info, t_philo *philo)
{
	philo->status = STATUS_EAT;
	philo->beg_eat_time = get_cur_time();
	show_message(philo, STATUS_EAT);
	my_sleep(info->time_to_eat, info);
	++(philo->eat_cnt);
#if 1
	if (info->num_of_must_eat\
		&& philo->eat_cnt == info->num_of_must_eat)
	{
		philo->eat_finished = 1;
		pthread_mutex_unlock(&(philo->eat_mutex));
	}
#endif
}
