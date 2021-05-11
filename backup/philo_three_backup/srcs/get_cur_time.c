#include "../incs/philo.h"

uint64_t
	get_cur_time()
{
	struct timeval	tmp;

	if (gettimeofday(&tmp, NULL) == -1)
		return (-1);
	return (tmp.tv_sec * SEC2MSEC + tmp.tv_usec * USEC2MSEC);
}
