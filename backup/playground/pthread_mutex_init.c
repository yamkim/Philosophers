#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t mutex_lock;

int g_count = 0;
#if 0
// data race case
void *t_function(void *data)
{
	void	*ret;
	char	*thread_name = (char *)data;
	g_count = 0;
	for (int i = 0; i < 3; ++i)
	{
		printf("%s COUNT %d\n", thread_name, g_count);
		++g_count;
		sleep(1);
	}
	return (ret);
}
#endif
// data race case
void *t_function(void *data)
{
	void	*ret;
	char	*thread_name = (char *)data;

	pthread_mutex_lock(&mutex_lock);
	g_count = 0;
	for (int i = 0; i < 3; ++i)
	{
		printf("%s COUNT %d\n", thread_name, g_count);
		++g_count;
		sleep(1);
	}
	pthread_mutex_unlock(&mutex_lock);
	return (ret);
}

int	main()
{
	pthread_t	p_thread[2];
	int			status;

	pthread_mutex_init(&mutex_lock, NULL);
	pthread_create(&p_thread[0], NULL, t_function, (void *)"Thread1");
	pthread_create(&p_thread[1], NULL, t_function, (void *)"Thread2");
	pthread_join(p_thread[0], (void *)&status);
	pthread_join(p_thread[1], (void *)&status);
}
