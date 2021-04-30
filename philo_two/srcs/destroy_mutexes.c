/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_mutexes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yekim <yekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 06:55:56 by yekim             #+#    #+#             */
/*   Updated: 2021/05/01 06:58:02 by yekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void
	*destroy_mutexes(t_info *info)
{
	int		idx;
	char	sem_name[255];

	(void)info;
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_SOMEONE_DEAD);
	idx = -1;
	while (++idx < info->num_of_philos)
	{
		memset(sem_name, 0, 255);
		gen_name_tag(sem_name, SEM_PHILO_EAT, idx);
		sem_unlink(sem_name);
	}
	sem_unlink(SEM_MSG);
	return (NULL);
}
