/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_message.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yekim <yekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 06:56:40 by yekim             #+#    #+#             */
/*   Updated: 2021/05/01 07:07:23 by yekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

static char
	*get_status_message(int status)
{
	if (status == STATUS_FORK)
		return ("has taken a fork");
	else if (status == STATUS_EAT)
		return ("is eating");
	else if (status == STATUS_SLEEP)
		return ("is sleeping");
	return ("died");
}

int
	show_message(t_philo *philo, int status)
{
	char		*status_msg;
	t_info		*info;
	uint64_t	dif_time;

	info = philo->info;
	if (sem_wait(info->msg_mutex))
		return (ERR_SEM_DO);
	if (info->program_finished)
		return (0);
	dif_time = get_cur_time() - info->beg_prog_time;
	status_msg = get_status_message(status);
	printf("%lld %d %s\n", dif_time, philo->pos, status_msg);
	if (status != STATUS_DIE)
	{
		info->msg_mutex_flag = 1;
		if (sem_post(info->msg_mutex))
			return (ERR_SEM_DO);
	}
	return (0);
}
