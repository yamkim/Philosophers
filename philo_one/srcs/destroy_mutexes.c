/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_mutexes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yekim <yekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 07:40:52 by yekim             #+#    #+#             */
/*   Updated: 2021/05/01 07:41:16 by yekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void
	*destroy_mutexes(t_info *info)
{
	int		idx;

	idx = -1;
	while (++idx < info->num_of_philos)
		pthread_mutex_destroy(&(info->fork_mutexes[idx]));
	idx = -1;
	while (++idx < info->num_of_philos)
		pthread_mutex_destroy(&(info->philos[idx].eat_mutex));
	pthread_mutex_destroy(&(info->msg_mutex));
	pthread_mutex_destroy(&(info->someone_dead_mutex));
	return (NULL);
}
