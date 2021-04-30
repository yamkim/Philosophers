#include "../incs/philo.h"

void
	my_sleep(uint64_t wait_time, t_info *info)
{
	uint64_t	goal_time;

	goal_time = wait_time + get_cur_time();
	while (goal_time > get_cur_time())
	{
		if (info->program_finished)
			return ;	
		usleep(100);
	}
}
