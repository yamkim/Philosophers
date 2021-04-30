/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yekim <yekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 06:56:38 by yekim             #+#    #+#             */
/*   Updated: 2021/05/01 07:06:11 by yekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

static int
	init_semaphores_for_philos(t_info *info)
{
	int		idx;
	char	sem_name[255];

	idx = -1;
	while (++idx < info->num_of_philos)
	{
		memset(sem_name, 0, 255);
		gen_name_tag(sem_name, SEM_PHILO_EAT, idx);
		info->philos[idx].eat_mutex = ft_sem_open(sem_name, 1);
		sem_unlink(sem_name);
		if ((info->philos[idx].eat_mutex) < 0)
			return (ERR_SEM_OPEN);
		if (sem_wait(info->philos[idx].eat_mutex))
			return (ERR_SEM_DO);
	}
	return (0);
}

static int
	init_semaphores(t_info *info)
{
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_MSG);
	sem_unlink(SEM_SOMEONE_DEAD);
	if ((info->fork_mutexes = ft_sem_open(SEM_FORK, info->num_of_philos)) < 0
		|| (info->msg_mutex = ft_sem_open(SEM_MSG, 1)) < 0
		|| (info->someone_dead_mutex = ft_sem_open(SEM_SOMEONE_DEAD, 1)) < 0
		|| init_semaphores_for_philos(info))
		return (ERR_SEM_OPEN);
	if (sem_wait(info->someone_dead_mutex))
		return (ERR_SEM_DO);
	return (0);
}

static int
	init_philos(t_info *info)
{
	int			idx;

	info->philos = (t_philo *)malloc(sizeof(t_philo) * info->num_of_philos);
	if (!info->philos)
		return (ERR_INIT_INFO);
	idx = -1;
	while (++idx < info->num_of_philos)
	{
		info->philos[idx].status = STATUS_THINK;
		info->philos[idx].pos = idx + 1;
		info->philos[idx].beg_eat_time = get_cur_time();
		info->philos[idx].eat_cnt = 0;
		info->philos[idx].info = info;
		info->philos[idx].eat_finished = 0;
	}
	return (0);
}

int
	init_info(
	t_info *info,
	int argc,
	char *argv[])
{
	(void)argc;
	info->num_of_philos = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->num_of_must_eat = ft_atoi(argv[5]);
	info->msg_mutex_flag = 0;
	info->program_finished = 0;
	if (init_philos(info))
		return (ERR_INIT_INFO);
	return (init_semaphores(info));
}
