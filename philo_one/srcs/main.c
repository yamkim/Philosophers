#include "../incs/philo.h"

#if 1
static void
	*is_all_eat(void *_info)
{
	int		idx;
	t_info	*info;

	info = (t_info *)_info;
	idx = -1;
	while (!(info->program_finished) && ++idx < info->num_of_philos)
		pthread_mutex_lock(&info->philos[idx].eat_mutex);
	if (idx == info->num_of_philos)
		pthread_mutex_unlock(&(info->someone_dead_mutex));
	info->program_finished = 1;
	return (NULL);
}
#endif

int
	run_threads(t_info *info)
{
	int			idx;
	void		*philo;
	pthread_t	tid;

#if 1
	if (info->num_of_must_eat)
	{
		if (pthread_create(&tid, NULL, &is_all_eat, info))
			return (ERR_INIT_THREAD);
		pthread_detach(tid);
	}
#endif
	idx = -1;
	info->beg_prog_time = get_cur_time();
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
	main(int argc, char *argv[]) {
	t_info	info;

	init_info(&info, argc, argv);
	run_threads(&info);

	pthread_mutex_lock(&(info.someone_dead_mutex));
	pthread_mutex_unlock(&(info.someone_dead_mutex));
	usleep(5 * SEC2MSEC);
	if (info.msg_mutex_flag)
		pthread_mutex_unlock(&info.msg_mutex);
	while (1);
	destroy_mutexes(&info);
	free_memory(&info);
	return (0);
}
