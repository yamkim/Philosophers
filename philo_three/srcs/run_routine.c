/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yekim <yekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 06:56:40 by yekim             #+#    #+#             */
/*   Updated: 2021/05/08 18:19:10 by yekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

static void
	*observe_program_finished(void *tmp_info)
{
	t_info	*info;

	info = (t_info *)tmp_info;
	if (sem_wait(info->finished_mutex))
		return (NULL);
	if (sem_post(info->finished_mutex))
		return (NULL);
	exit(0);
}

static void
	*observe_philo_status(void *tmp_philo)
{
	t_philo		*philo;
	t_info		*info;
	uint64_t	dif_time;

	philo = (t_philo *)tmp_philo;
	info = philo->info;
	while (1)
	{
		if (philo->eat_finished)
			exit(0);
		dif_time = get_cur_time() - philo->beg_eat_time;
		if (!(philo->status == STATUS_EAT) \
				&& dif_time > info->time_to_die)
		{
			if (do_die(info, philo))
				return (NULL);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}

void
	*run_routine(void *tmp_philo)
{
	t_info		*info;
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo *)tmp_philo;
	info = philo->info;
	if (pthread_create(&tid, NULL, &observe_program_finished, info))
		return (NULL);
	pthread_detach(tid);
	if (pthread_create(&tid, NULL, &observe_philo_status, philo))
		return (NULL);
	pthread_detach(tid);
	while (1)
	{
		if (philo->eat_finished)
			exit(0);
		if (take_fork(info, philo))
			return (NULL);
		if (do_eat(info, philo))
			return (NULL);
		if (return_fork(info, philo))
			return (NULL);
		if (philo->eat_finished)
			exit(0);
		if (do_sleep(info, philo))
			return (NULL);
	}
	return (NULL);
}
