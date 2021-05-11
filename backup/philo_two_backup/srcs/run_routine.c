#include "../incs/philo.h"

static void
    *exit_philo_thread(t_philo *philo)
{
	char	sem_name[255];

	memset(sem_name, 0, 255);
	gen_name_tag(sem_name, philo->pos - 1);
    sem_unlink(sem_name);
    return (NULL);
}

void
	*run_routine(void *_philo)
{
	t_info		*info;
	t_philo		*philo;

	philo = (t_philo *)_philo;
	info = philo->info;
	while (1)
	{
		if (info->someone_dead)
			return (exit_philo_thread(philo));

		if (take_fork(info, philo))
			return (NULL);
		if (do_eat(info, philo))
			return (NULL);
		if (return_fork(info, philo))
			return (NULL);
		if (info->finished_thread[philo->pos - 1])
			return (exit_philo_thread(philo));

		if (info->someone_dead)
			return (exit_philo_thread(philo));
		if (do_sleep(info, philo))
			return (NULL);
	}
	return (NULL);
}
