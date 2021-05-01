/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yekim <yekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 07:40:54 by yekim             #+#    #+#             */
/*   Updated: 2021/05/01 07:40:55 by yekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void
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
