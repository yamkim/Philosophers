/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_die.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yekim <yekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 06:56:01 by yekim             #+#    #+#             */
/*   Updated: 2021/05/08 18:19:19 by yekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int
	do_die(t_info *info, t_philo *philo)
{
	int	idx;

	show_message(philo, STATUS_DIE);
	idx = -1;
#if 1
	if (info->num_of_must_eat > 0)
	{
		while (++idx < info->num_of_philos)
		{
			if (info->philos[idx].eat_finished)
				continue ;
			if (sem_post(info->philos[idx].eat_mutex))
				return (ERR_SEM_DO);
		}
	}
#endif
	if (sem_post(info->someone_dead_mutex))
		return (ERR_SEM_DO);
	if (sem_post(info->finished_mutex))
		return (ERR_SEM_DO);
	exit(0);
	return (0);
}
