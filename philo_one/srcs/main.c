/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yekim <yekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 07:40:56 by yekim             #+#    #+#             */
/*   Updated: 2021/05/03 15:44:02 by yekim            ###   ########.fr       */
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
		pthread_mutex_lock(&info->philos[idx].eat_mutex);
	if (!info->program_finished)
	{
		info->program_finished = 1;
		pthread_mutex_unlock(&(info->someone_dead_mutex));
	}
	return (NULL);
}

int
	run_threads(t_info *info)
{
	int			idx;
	void		*philo;
	pthread_t	tid;

	if (info->num_of_must_eat)
	{
		if (pthread_create(&tid, NULL, &is_all_eat, info))
			return (ERR_INIT_THREAD);
		pthread_detach(tid);
	}
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
	main(int argc, char *argv[])
{
	t_info	info;

	if (!(argc == 5 || argc == 6))
		return (print_error("Error: bad arguments\n"));
	if (init_info(&info, argc, argv)
		|| run_threads(&info))
		return (exit_program(&info) && print_error("Error: fatal\n"));
	pthread_mutex_lock(&(info.someone_dead_mutex));
	pthread_mutex_unlock(&(info.someone_dead_mutex));
	usleep(5 * SEC2MSEC);
	if (info.msg_mutex_lock_flag)
		pthread_mutex_unlock(&info.msg_mutex);
	while (1);
	exit_program(&info);
	return (0);
}
