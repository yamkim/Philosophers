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

# define SEM_INFO "SEM_INFO"
# define SEM_PHILO "SEM_PHILO"
# define SEM_FORK "SEM_FORK"

# define ERR_INIT_THREAD 1
# define ERR_SEM_OPEN 1
# define ERR_INIT_INFO 1
# define ERR_SEM_DO 1

# define SEC2USEC 1000
# define MSEC2USEC 1000
# define USEC2MSEC 1/1000

# define MAX_NUM_OF_PHILOS 200

typedef	struct	s_info
{
	sem_t		*mutex;
	uint64_t	beg_prog_time;
	uint64_t	cur_time;
	int			num_of_philos;
	uint64_t	time_to_die;
	uint64_t	time_to_eat;
	uint64_t	time_to_sleep;
	int			num_of_must_eat;
	int			finished_thread[200];
	sem_t		*fork_mutexes;
	int			someone_dead;
	struct s_philo	\
				*philos;
}				t_info;

typedef struct	s_philo
{
	sem_t		*mutex;
	int			pos;
	int			status;
	uint64_t	beg_eat_time;
	int			lfork;
	int			rfork;
	int			eat_cnt;
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
size_t
	ft_strlcpy(char *dest, const char *src, size_t size);
size_t
	ft_strlen(const char *str);
void
	gen_name_tag(char *name, int nbr);

/*
** show_message.c
*/
int
	show_message(t_philo *philo, int status);

/*
** get_cur_time.c
*/
uint64_t
	get_cur_time();

/*
** do_eat.c
*/
int
	do_eat(t_info *info, t_philo *philo);

/*
** do_sleep.c
*/
int
	do_sleep(t_info *info, t_philo *philo);

/*
** do_die.c
*/
int
	do_die(t_info *info, t_philo *philo);

/*
** run_routine.c
*/
void
	*run_routine(void *philo);

/*
** take_fork.c
*/
int
	take_fork(t_info *info, t_philo *philo);
int
	return_fork(t_info *info, t_philo *philo);

/*
** exit_threads.c
*/
void
	*exit_threads(t_info *info);

/*
** ft_sem_open.c
*/
sem_t
	*ft_sem_open(char *name, int value);

/*
** free_memory.c
*/
void
	free_memory(t_info *info);

#endif
