/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yekim <yekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 07:40:57 by yekim             #+#    #+#             */
/*   Updated: 2021/05/01 10:20:07 by yekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

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
	*run_routine(void *tmp_philo)
{
	t_info		*info;
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo *)tmp_philo;
	info = philo->info;
	if (pthread_create(&tid, NULL, &observe_philo_status, philo))
		return (NULL);
	pthread_detach(tid);
	while (1)
	{
		if (info->program_finished || philo->eat_finished)
			return (NULL);
		take_fork(info, philo);
		do_eat(info, philo);
		return_fork(info, philo);
		if (info->program_finished || philo->eat_finished)
			return (NULL);
		do_sleep(info, philo);
	}
	return (NULL);
}
