/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yekim <yekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 07:40:54 by yekim             #+#    #+#             */
/*   Updated: 2021/05/01 07:40:54 by yekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void
	do_sleep(t_info *info, t_philo *philo)
{
	philo->status = STATUS_SLEEP;
	show_message(philo, STATUS_SLEEP);
	my_sleep(info->time_to_sleep, info);
}
