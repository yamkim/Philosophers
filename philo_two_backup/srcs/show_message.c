#include "../incs/philo.h"

static char
	*get_status_message(int status)
{
	if (status == STATUS_FORK)
		return("has taken a fork");
	else if  (status == STATUS_EAT)
		return("is eating");
	else if  (status == STATUS_SLEEP)
		return("is sleeping");
	return ("died");
}

int
	show_message(t_philo *philo, int status)
{
	char		*status_msg;
	t_info		*info;
	uint64_t	dif_time;

	info = philo->info;
	dif_time = get_cur_time() - info->beg_prog_time;
	status_msg = get_status_message(status);
	if (info->someone_dead)
		return (1);
	printf("%lld %d %s\n", dif_time, philo->pos, status_msg);
	return (0);
}
