#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	handle_error(void)
{
    perror("thread create error : ");
    exit(0);
}
 
// 쓰레드 함수
void *t_function(void *data)
{
	char		a[100000];
	static int	num = 0;
	num = *(int *)data;

	printf("Thread Start\n");
	sleep(10);
	printf("Thread end\n");
	return (void *)&num;
}

int	main()
{
	pthread_t	p_thread;
	int	thread_id;
	int	status;
	int	a = 100;

	printf("Before Creating Thread\n");
	thread_id = pthread_create(&p_thread, NULL, t_function, (void *)&a);
	if (thread_id < 0)
		handle_error();
	pthread_detach(p_thread);
	pause();
	return (0);
}
