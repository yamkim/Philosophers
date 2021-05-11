/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yekim <yekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 06:56:39 by yekim             #+#    #+#             */
/*   Updated: 2021/05/11 13:57:59 by yekim            ###   ########.fr       */
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
	if (sem_post(info->someone_dead_mutex))
		return (NULL);
	return (NULL);
}

static int
	run_philos(t_info *info)
{
	int			idx;
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
		info->philos[idx].pid = fork();
		if (info->philos[idx].pid < 0)
			return (1);
		else if (info->philos[idx].pid == 0)
		{
			run_routine(&(info->philos[idx]));
			exit(0);
		}
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
		return (exit_program(&info) && print_error("Error: fatal\n"));
	if (run_philos(&info))
		return (exit_program(&info) && print_error("Error: fatal\n"));
	if (sem_wait(info.someone_dead_mutex))
		return (ERR_SEM_DO);
	if (sem_post(info.someone_dead_mutex))
		return (ERR_SEM_DO);
	usleep(5 * SEC2MSEC);
	exit_program(&info);
	return (0);
}
