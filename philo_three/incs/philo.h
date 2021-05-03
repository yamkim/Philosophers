/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yekim <yekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 07:26:35 by yekim             #+#    #+#             */
/*   Updated: 2021/05/04 08:35:16 by yekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PHILO_H
# define _PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <string.h>
# include <semaphore.h>

# define STATUS_EAT 0
# define STATUS_SLEEP 1
# define STATUS_FORK 2
# define STATUS_THINK 3
# define STATUS_DIE 4

# define ERR_INIT_THREAD 1
# define ERR_INIT_INFO 1
# define ERR_SEM_OPEN 1
# define ERR_SEM_DO 1

# define SEC2MSEC 1000
# define MSEC2USEC 1000
# define USEC2MSEC 0.001

# define SEM_PHILO_EAT "SEM_PHILO_EAT"
# define SEM_PHILO "SEM_PHILO"
# define SEM_FORK "SEM_FORKS"
# define SEM_MSG "SEM_MSG"
# define SEM_SOMEONE_DEAD "SEM_SOMEONE_DEAD"

# define MAX_NUM_OF_PHILOS 200

typedef	struct		s_info
{
	uint64_t		beg_prog_time;
	uint64_t		cur_time;
	int				num_of_philos;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				num_of_must_eat;
	int				program_finished;
	sem_t			*fork_mutexes;
	int				msg_mutex_flag;
	sem_t			*msg_mutex;
	sem_t			*someone_dead_mutex;
	struct s_philo	*philos;
}					t_info;

typedef struct		s_philo
{
	pid_t			pid;
	int				pos;
	int				status;
	uint64_t		beg_eat_time;
	int				eat_cnt;
	int				eat_finished;
	sem_t			*eat_mutex;
	t_info			*info;
}					t_philo;

/*
** init_info.c
*/
int					init_info(
					t_info *info,
					int argc,
					char *argv[]);

/*
** run_routine.c
*/
void				*run_routine(
					void *tmp_philo);

/*
** ft_utils.c
*/
size_t				ft_strlen(
					const char *str);
int					ft_atoi(
					const char *nptr);
void				ft_putnbr_fd(
					int n, int fd);
void				gen_name_tag(
					char *name,
					char *type,
					int nbr);

/*
** show_message.c
*/
int					show_message(
					t_philo *philo,
					int status);

/*
** get_cur_time.c
*/
uint64_t			get_cur_time(void);

/*
** my_sleep.c
*/
void				my_sleep(
					uint64_t wait_time,
					t_info *info);

/*
** do_eat.c
*/
int					do_eat(
					t_info *info,
					t_philo *philo);

/*
** do_sleep.c
*/
int					do_sleep(
					t_info *info,
					t_philo *philo);

/*
** do_die.c
*/
int					do_die(
					t_info *info,
					t_philo *philo);

/*
** take_fork.c
*/
int					take_fork(
					t_info *info,
					t_philo *philo);
int					return_fork(
					t_info *info,
					t_philo *philo);

/*
** ft_sem_open.c
*/
sem_t				*ft_sem_open(
					char *name,
					int value);

/*
** exit_program.c
*/
int					exit_program(
					t_info *info);

/*
** print_error.c
*/
int					print_error(
					char *str);
#endif
