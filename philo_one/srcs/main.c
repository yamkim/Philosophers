/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yekim <yekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 07:40:56 by yekim             #+#    #+#             */
/*   Updated: 2021/05/10 09:55:10 by yekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

#if 1
static void
	*is_all_eat(void *tmp_info)
{
	int		idx;
	t_info	*info;

	info = (t_info *)tmp_info;
	idx = -1;
	while (++idx < info->num_of_philos)
		pthread_mutex_lock(&info->philos[idx].eat_mutex);
	if (!info->program_finished)
	{
		info->program_finished = 1;
		pthread_mutex_unlock(&(info->someone_dead_mutex));
	}
	return (NULL);
}
#endif

int
	run_threads(t_info *info)
{
	int			idx;
	void		*philo;

	if (info->num_of_must_eat)
	{
		if (pthread_create(&(info->tid), NULL, &is_all_eat, info))
			return (ERR_INIT_THREAD);
		pthread_detach(info->tid);
	}
	idx = -1;
	info->beg_prog_time = get_cur_time();
	while (++idx < info->num_of_philos)
	{
		philo = (void *)(&info->philos[idx]);
		if (pthread_create(&(((t_philo *)philo)->tid), NULL, &run_routine, philo))
			return (ERR_INIT_THREAD);
		usleep(100);
	}
	return (0);
}

int
	main(int argc, char *argv[])
{
	t_info	info;

	if (!(argc == 5 || argc == 6))
		return (print_error("Error: bad arguments\n"));
	if (init_info(&info, argc, argv))
		return (print_error("Error: fatal\n"));
	if (run_threads(&info))
		return (print_error("Error: fatal\n"));
	pthread_mutex_lock(&(info.someone_dead_mutex));
	pthread_mutex_unlock(&(info.someone_dead_mutex));
	usleep(50 * SEC2MSEC);
	if (info.msg_mutex_lock_flag)
		pthread_mutex_unlock(&info.msg_mutex);
	exit_program(&info);
	return (0);
}
