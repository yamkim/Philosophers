/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yekim <yekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 06:56:39 by yekim             #+#    #+#             */
/*   Updated: 2021/05/08 18:21:59 by yekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

#if 1
static void
	*is_all_eat(void *tmp_info)
{
	int		idx;
	t_info	*info;

	info = (t_info *)tmp_info;
	idx = -1;
	while (++idx < info->num_of_philos)
	{
		if (sem_wait(info->philos[idx].eat_mutex))
			return (NULL);
	}
	if (sem_post(info->someone_dead_mutex))
		return (NULL);
	return (NULL);
}
#endif

int
	run_philos(t_info *info)
{
	int			idx;
	t_philo		philo;
	pthread_t	tid;

#if 1
	if (info->num_of_must_eat)
	{
		if (pthread_create(&tid, NULL, &is_all_eat, info))
			return (ERR_INIT_THREAD);
		pthread_detach(tid);
	}
#endif
	idx = -1;
	info->beg_prog_time = get_cur_time();
	while (++idx < info->num_of_philos)
	{
		philo = (t_philo)(info->philos[idx]);
		philo.pid = fork();
		if (philo.pid < 0)
			return (1);
		else if (philo.pid == 0)
		{
			run_routine(&philo);
			exit(0);
		}
		usleep(100);
	}
	return (0);
}

int
	main(int argc, char *argv[])
{
	t_info	info;

	if (!(argc == 5 || argc == 6))
		return (print_error("Error: bad arguments\n"));
	if (init_info(&info, argc, argv))
		return (exit_program(&info) && print_error("Error: fatal\n"));
	if (run_philos(&info))
		return (exit_program(&info) && print_error("Error: fatal\n"));
	if (sem_wait(info.someone_dead_mutex))
		return (ERR_SEM_DO);
	if (sem_post(info.someone_dead_mutex))
		return (ERR_SEM_DO);
	usleep(5 * SEC2MSEC);
	exit_program(&info);
	return (0);
}
