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
	int	num = *(int *)data;
	int	*ret = malloc(sizeof(int));

	printf("num: %d\n", num);
	sleep(1);

	*ret = num * num;
	printf("t_function is finished\n");
	return (void*)ret;
}
 
int main()
{
    pthread_t p_thread;
    int thread_id;
    int *res = malloc(sizeof(int));
	int	num = 100;
    char p1[] = "thread_1";   // 1번 쓰레드 이름
    char p2[] = "thread_2";   // 2번 쓰레드 이름
    char pM[] = "thread_m";   // 메인 쓰레드 이름
 
    sleep(1);  // 2초 대기후 쓰레드 생성
 
    // ① 1번 쓰레드 생성
    // 쓰레드 생성시 함수는 t_function
    // t_function 의 매개변수로 p1 을 넘긴다.
    thread_id = pthread_create(&p_thread, NULL, t_function, (void *)&num);
    if (thread_id < 0)
		handle_error();
 
    // 쓰레드 종료를 기다린다. 
    pthread_join(p_thread, (void *)&res);
	printf("res of t_function: %d\n", *(int *)res);
	free(res);
 
    printf("Program is Finished\n");
 
    return 0;
}
