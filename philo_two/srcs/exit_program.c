/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yekim <yekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 06:55:56 by yekim             #+#    #+#             */
/*   Updated: 2021/05/10 10:07:41 by yekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

static void
	free_memories(t_info *info)
{
	if (info->philos)
		free(info->philos);
}

int
	exit_program(t_info *info)
{
	int		idx;
	char	sem_name[255];
	int		status;

	(void)info;
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_SOMEONE_DEAD);
	idx = -1;
	while (++idx < info->num_of_philos)
		pthread_join(info->philos[idx].tid, (void **)&status);
	if (info->num_of_must_eat)
		pthread_join(info->tid, (void **)&status);
	idx = -1;
	while (++idx < info->num_of_philos)
	{
		memset(sem_name, 0, 255);
		gen_name_tag(sem_name, SEM_PHILO_EAT, idx);
		sem_unlink(sem_name);
	}
	sem_unlink(SEM_MSG);
	free_memories(info);
	return (1);
}
