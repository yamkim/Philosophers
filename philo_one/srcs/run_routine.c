#include "../incs/philo.h"

static void
	*observe_philo_status(void *_philo)
{
	t_philo		*philo;
	t_info		*info;
	uint64_t	dif_time;

	philo = (t_philo *)_philo;
	info = philo->info;
	while(1)
	{
		if (info->program_finished || philo->eat_finished)
			return (NULL);
		dif_time = get_cur_time() - philo->beg_eat_time;
		if (!(philo->status == STATUS_EAT) \
				&& dif_time > info->time_to_die)
		{
			do_die(info, philo);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}

void
	*run_routine(void *_philo)
{
	t_info		*info;
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo *)_philo;
	info = philo->info;
	if (pthread_create(&tid, NULL, &observe_philo_status, philo))
		return (NULL);
	pthread_detach(tid);
	while (1)
	{
#if 1
		if (info->program_finished || philo->eat_finished)
			return (NULL);
#endif
		take_fork(info, philo);
		do_eat(info, philo);
		return_fork(info, philo);
		if (info->program_finished || philo->eat_finished)
			return (NULL);
		do_sleep(info, philo);
	}
	return (NULL);
}
