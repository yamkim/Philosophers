/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_die.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yekim <yekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 07:40:53 by yekim             #+#    #+#             */
/*   Updated: 2021/05/01 09:34:27 by yekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void
	do_die(t_info *info, t_philo *philo)
{
	int	idx;

	if (info->program_finished)
		return ;
	show_message(philo, STATUS_DIE);
	idx = -1;
	if (info->num_of_must_eat > 0)
	{
		while (++idx < info->num_of_philos)
		{
			if (info->philos[idx].eat_finished)
				continue ;
			pthread_mutex_unlock(&info->philos[idx].eat_mutex);
		}
	}
	info->program_finished = 1;
	pthread_mutex_unlock(&(info->someone_dead_mutex));
}
