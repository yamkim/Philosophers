/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yekim <yekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 07:40:52 by yekim             #+#    #+#             */
/*   Updated: 2021/05/10 10:04:49 by yekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

static void
	free_memory(t_info *info)
{
	if (info->fork_mutexes != NULL)
	{
		free(info->fork_mutexes);
		info->fork_mutexes = NULL;
	}
	if (info->philos != NULL)
	{
		free(info->philos);
		info->philos = NULL;
	}
}

int
	exit_program(t_info *info)
{
	int		idx;
	int		status;

	idx = -1;
	while (++idx < info->num_of_philos)
		pthread_join(info->philos[idx].tid, (void **)&status);
	if (info->num_of_must_eat)
		pthread_join(info->tid, (void **)&status);
	while (++idx < info->num_of_philos)
		pthread_mutex_destroy(&(info->fork_mutexes[idx]));
	idx = -1;
	while (++idx < info->num_of_philos)
		pthread_mutex_destroy(&(info->philos[idx].eat_mutex));
	pthread_mutex_destroy(&(info->msg_mutex));
	pthread_mutex_destroy(&(info->someone_dead_mutex));
	free_memory(info);
	return (1);
}
