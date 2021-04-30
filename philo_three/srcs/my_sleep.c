#include "../incs/philo.h"

void
	my_sleep(uint64_t wait_time)
{
	uint64_t	goal_time;

	goal_time = wait_time + get_cur_time();
	while (goal_time > get_cur_time())
		usleep(100);
}

