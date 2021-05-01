/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yekim <yekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 07:40:56 by yekim             #+#    #+#             */
/*   Updated: 2021/05/01 08:15:33 by yekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

static int
	init_mutexes(t_info *info)
{
	int		size;
	int		idx;

	size = sizeof(pthread_mutex_t) * info->num_of_philos;
	info->fork_mutexes = (pthread_mutex_t *)malloc(size);
	if (!info->fork_mutexes)
		return (ERR_INIT_INFO);
	idx = -1;
	while (++idx < info->num_of_philos)
		pthread_mutex_init(&(info->fork_mutexes[idx]), NULL);
	pthread_mutex_init(&(info->msg_mutex), NULL);
	pthread_mutex_init(&(info->someone_dead_mutex), NULL);
	pthread_mutex_lock(&(info->someone_dead_mutex));
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
		info->philos[idx].lfork = idx;
		info->philos[idx].rfork = (idx + 1) % info->num_of_philos;
		info->philos[idx].eat_cnt = 0;
		info->philos[idx].info = info;
		info->philos[idx].eat_finished = 0;
		pthread_mutex_init(&(info->philos[idx].eat_mutex), NULL);
		pthread_mutex_lock(&(info->philos[idx].eat_mutex));
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
	info->program_finished = 0;
	info->msg_mutex_lock_flag = 0;
	if (init_philos(info))
		return (ERR_INIT_INFO);
	return (init_mutexes(info));
}
