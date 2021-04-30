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

void
	show_message(t_philo *philo, int status)
{
	char		*status_msg;
	t_info		*info;
	uint64_t	dif_time;

	info = philo->info;
	pthread_mutex_lock(&info->msg_mutex);
	if (info->program_finished)
		return ;
	dif_time = get_cur_time() - info->beg_prog_time;
	status_msg = get_status_message(status);
	printf("%lld %d %s\n", dif_time, philo->pos, status_msg);
	if (status != STATUS_DIE)
	{
		info->msg_mutex_flag = 1;
		pthread_mutex_unlock(&info->msg_mutex);
	}
}
