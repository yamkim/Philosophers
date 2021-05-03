/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yekim <yekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 06:56:35 by yekim             #+#    #+#             */
/*   Updated: 2021/05/01 06:58:42 by yekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int
	do_sleep(t_info *info, t_philo *philo)
{
	philo->status = STATUS_SLEEP;
	show_message(philo, STATUS_SLEEP);
	my_sleep(info->time_to_sleep, info);
	return (0);
}
