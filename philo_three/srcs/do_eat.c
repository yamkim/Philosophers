/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yekim <yekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 06:56:18 by yekim             #+#    #+#             */
/*   Updated: 2021/05/08 18:21:05 by yekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int
	do_eat(t_info *info, t_philo *philo)
{
	philo->status = STATUS_EAT;
	philo->beg_eat_time = get_cur_time();
	show_message(philo, STATUS_EAT);
	my_sleep(info->time_to_eat, info);
	++(philo->eat_cnt);
	if (info->num_of_must_eat > 0\
		&& philo->eat_cnt == info->num_of_must_eat)
	{
		philo->eat_finished = 1;
		if (sem_post(philo->eat_mutex))
			return (ERR_SEM_DO);
		if (sem_post(info->finished_mutex))
			return (ERR_SEM_DO);
	}
	return (0);
}
