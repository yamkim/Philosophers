#include "../incs/philo.h"

#if 1
static int
	is_all_philos_eat_must(t_info *info)
{
	int	idx;

	idx = -1;
	while (++idx < info->num_of_philos)
	{
		if (!(info->finished_thread[idx]))
			break ;
	}
	if (idx == info->num_of_philos)
		return(1);
	return (0);
}
#endif

#if 1
static void
	*do_observe_philos_status(void *_info)
{
	t_info		*info;
	t_philo		*philo;
	int			idx;
	uint64_t	dif_time;

	info = (t_info *)_info;
	while(1)
	{
		idx = -1;
		while (++idx < info->num_of_philos)
		{
			philo = &(info->philos[idx]);
			if (sem_wait(philo->mutex) != 0)
				return (NULL);

			dif_time = get_cur_time() - philo->beg_eat_time;
			if (!(philo->status == STATUS_EAT) && dif_time > info->time_to_die)
			{
				if (do_die(info, philo))
					return (NULL);
				if (sem_post(philo->mutex))
					return (NULL);
				return (NULL);
			}

			if (sem_post(philo->mutex))
				return (NULL);
			//usleep(100);
		}
	}
	return (NULL);
}
#endif

int
	run_threads(t_info *info)
{
	int			idx;
	void		*philo;
	pthread_t	tid;

	idx = -1;
	info->beg_prog_time = get_cur_time();
	if (pthread_create(&tid, NULL, &do_observe_philos_status, info))
		return (ERR_INIT_THREAD);
	pthread_detach(tid);
	while (++idx < info->num_of_philos)
	{
		philo = (void *)(&info->philos[idx]);
		if (pthread_create(&tid, NULL, &run_routine, philo))
			return (ERR_INIT_THREAD);
		pthread_detach(tid);
		usleep(100);
	}
	return (0);
}

int
	main(int argc, char *argv[])
{
	t_info	info;

	init_info(&info, argc, argv);
	run_threads(&info);
	while (1)
	{
		if (sem_wait(info.mutex))
			return (1);
		if (info.someone_dead)
		{
			if (sem_post(info.mutex))
				return (1);
			break ;
		}
		if (is_all_philos_eat_must(&info))
		{
			if (sem_post(info.mutex))
				return (1);
			break ;
		}
		if (sem_post(info.mutex))
			return (1);
		usleep(10 * USEC2MSEC);
	}
	exit_threads(&info);
	//free_memory(&info);
	return (0);
}
