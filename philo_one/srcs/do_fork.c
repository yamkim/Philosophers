/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yekim <yekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 07:40:54 by yekim             #+#    #+#             */
/*   Updated: 2021/05/01 10:18:54 by yekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void
	take_fork(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&(info->fork_mutexes[philo->lfork]));
	show_message(philo, STATUS_FORK);
	pthread_mutex_lock(&(info->fork_mutexes[philo->rfork]));
	show_message(philo, STATUS_FORK);
}

void
	return_fork(t_info *info, t_philo *philo)
{
	pthread_mutex_unlock(&(info->fork_mutexes[philo->lfork]));
	pthread_mutex_unlock(&(info->fork_mutexes[philo->rfork]));
}
