/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yekim <yekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 07:40:56 by yekim             #+#    #+#             */
/*   Updated: 2021/05/01 07:46:57 by yekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void
	my_sleep(uint64_t wait_time, t_info *info)
{
	uint64_t	goal_time;

	goal_time = wait_time + get_cur_time();
	while (goal_time > get_cur_time())
	{
		if (info->program_finished)
			return ;
		usleep(100);
	}
}
