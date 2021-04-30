/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cur_time.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yekim <yekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 06:56:38 by yekim             #+#    #+#             */
/*   Updated: 2021/05/01 06:59:17 by yekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

uint64_t
	get_cur_time(void)
{
	struct timeval	tmp;

	if (gettimeofday(&tmp, NULL) == -1)
		return (-1);
	return (tmp.tv_sec * SEC2MSEC + tmp.tv_usec * USEC2MSEC);
}
