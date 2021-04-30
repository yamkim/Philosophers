#ifndef _PHILO_H
# define _PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <string.h>

# define STATUS_EAT 0
# define STATUS_SLEEP 1
# define STATUS_FORK 2
# define STATUS_THINK 3
# define STATUS_DIE 4

# define ERR_INIT_THREAD 1
# define ERR_INIT_INFO 1

# define SEC2MSEC (uint64_t)1000
# define MSEC2USEC 1000
# define USEC2MSEC 0.001

# define MAX_NUM_OF_PHILOS 200

typedef	struct	s_info
{
	uint64_t	beg_prog_time;
	uint64_t	cur_time;
	int			num_of_philos;
	uint64_t	time_to_die;
	uint64_t	time_to_eat;
	uint64_t	time_to_sleep;
	int			num_of_must_eat;
	int			program_finished;
	pthread_mutex_t \
				*fork_mutexes;
	pthread_mutex_t \
				someone_dead_mutex;
	int			msg_mutex_flag;
	pthread_mutex_t \
				msg_mutex;
	struct s_philo	\
				*philos;
}				t_info;

typedef struct	s_philo
{
	int			pos;
	int			status;
	uint64_t	beg_eat_time;
	int			lfork;
	int			rfork;
	int			eat_cnt;
	int			eat_finished;
	pthread_mutex_t \
				eat_mutex;
	t_info		*info;
}				t_philo;

/*
** init_info.c
*/
int
	init_info(
	t_info *info,
	int argc,
	char *argv[]);

/*
** ft_utils.c
*/
int
	ft_atoi(const char *nptr);
void
	ft_putnbr_fd(int n, int fd);

/*
** show_message.c
*/
void
	show_message(t_philo *philo, int status);

/*
** get_cur_time.c
*/
uint64_t
	get_cur_time();

/*
** do_eat.c
*/
void
	do_eat(t_info *info, t_philo *philo);

/*
** do_sleep.c
*/
void
	do_sleep(t_info *info, t_philo *philo);

/*
** do_die.c
*/
void
	do_die(t_info *info, t_philo *philo);

/*
** run_routine.c
*/
void
	*run_routine(void *philo);

/*
** take_fork.c
*/
void
	take_fork(t_info *info, t_philo *philo);
void
	return_fork(t_info *info, t_philo *philo);

/*
** my_sleep.c
*/
void
	my_sleep(uint64_t wait_time, t_info *info);

/*
** destroy_mutexes.c
*/
void
	*destroy_mutexes(t_info *info);

/*
** free_memory.c
*/
void
	free_memory(t_info *info);

#endif
