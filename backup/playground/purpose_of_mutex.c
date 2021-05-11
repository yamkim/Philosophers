#if 0
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

typedef pthread_mutex_t mutex_t;

#define COUNT_LIMIT 5

typedef struct	s_info
{
	mutex_t		flag;
	int			count;
}				t_info;


void
	init_info(t_info *info)
{	
	info->count = 0;
	pthread_mutex_init(&(info->flag), NULL);
	pthread_mutex_lock(&(info->flag));
}

void
	*run(void *_info)
{
	t_info *info;

	info = (t_info *)_info;
	while (1)
	{
		++(info->count);
		printf("info->count: %d\n", info->count);
		if ((info->count) == COUNT_LIMIT)
		{
			pthread_mutex_unlock(&(info->flag));
			return (NULL);
		}
		sleep(1);
	}
}

int
	main(void)
{
	t_info		info;
	pthread_t	tid;

	printf("Program Start\n");
	init_info(&info);
	if (pthread_create(&tid, NULL, &run, &info))
		return (1);
	pthread_detach(tid);

	pthread_mutex_lock(&(info.flag));
	pthread_mutex_unlock(&(info.flag));
	printf("Program End\n");

	return (0);
}
#endif

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>


#define COUNT_LIMIT 5

typedef struct	s_info
{
	bool		flag;
	int			count;
}				t_info;

void
	init_info(t_info *info)
{	
	info->count = 0;
	info->flag = false;
}

void
	*run(void *_info)
{
	t_info *info;

	info = (t_info *)_info;
	while (1)
	{
		++(info->count);
		printf("info->count: %d\n", info->count);
		if ((info->count) == COUNT_LIMIT)
		{
			info->flag = true;
			return (NULL);
		}
		sleep(1);
	}
}

int
	main(void)
{
	t_info		info;
	pthread_t	tid;

	printf("Program Start\n");
	init_info(&info);
	if (pthread_create(&tid, NULL, &run, &info))
		return (1);
	pthread_detach(tid);

	while (1)
	{
		if (info.flag)
			break;
	}
	printf("Program End\n");

	return (0);
}
