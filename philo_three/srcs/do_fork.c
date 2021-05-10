/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yekim <yekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 06:56:31 by yekim             #+#    #+#             */
/*   Updated: 2021/05/10 10:44:45 by yekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int
	take_fork(t_info *info, t_philo *philo)
{
	if (philo->eat_finished)
		exit(0);
	if (sem_wait(info->fork_mutexes))
		return (ERR_SEM_DO);
	if (show_message(philo, STATUS_FORK))
		return (ERR_SEM_DO);
	if (sem_wait(info->fork_mutexes))
		return (ERR_SEM_DO);
	if (show_message(philo, STATUS_FORK))
		return (ERR_SEM_DO);
	return (0);
}

int
	return_fork(t_info *info, t_philo *philo)
{
	(void)philo;
	if (sem_post(info->fork_mutexes))
		return (ERR_SEM_DO);
	if (sem_post(info->fork_mutexes))
		return (ERR_SEM_DO);
	return (0);
}
