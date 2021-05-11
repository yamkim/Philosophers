#include "../incs/philo.h"

int
	do_sleep(t_info *info, t_philo *philo)
{
	philo->status = STATUS_SLEEP;
	show_message(philo, STATUS_SLEEP);
	my_sleep(info->time_to_sleep);
	return (0);
}

