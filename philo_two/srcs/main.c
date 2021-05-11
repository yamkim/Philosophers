/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yekim <yekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 06:56:39 by yekim             #+#    #+#             */
/*   Updated: 2021/05/11 14:05:56 by yekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

static void
	*is_all_eat(void *tmp_info)
{
	int		idx;
	t_info	*info;

	info = (t_info *)tmp_info;
	idx = -1;
	while (++idx < info->num_of_philos)
	{
		if (sem_wait(info->philos[idx].eat_mutex))
			return (NULL);
	}
	if (!info->program_finished)
	{
		info->program_finished = 1;
		if (sem_post(info->someone_dead_mutex))
			return (NULL);
	}
	return (NULL);
}

int
	run_threads(t_info *info)
{
	int			idx;
	void		*philo;
	pthread_t	*tmp_tid;

	if (info->num_of_must_eat)
	{
		if (pthread_create(&(info->tid), NULL, &is_all_eat, info))
			return (ERR_INIT_THREAD);
	}
	idx = -1;
	info->beg_prog_time = get_cur_time();
	while (++idx < info->num_of_philos)
	{
		philo = (void *)(&info->philos[idx]);
		tmp_tid = &(((t_philo *)philo)->tid);
		if (pthread_create(tmp_tid, NULL, &run_routine, philo))
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
	if (init_info(&info, argc, argv)
		|| run_threads(&info))
		return (exit_program(&info) && print_error("Error: fatal\n"));
	if (sem_wait(info.someone_dead_mutex))
		return (ERR_SEM_DO);
	if (sem_post(info.someone_dead_mutex))
		return (ERR_SEM_DO);
	usleep(50 * SEC2MSEC);
	if (info.msg_mutex_flag)
	{
		if (sem_post(info.msg_mutex))
			return (ERR_SEM_DO);
	}
	exit_program(&info);
	return (0);
}
