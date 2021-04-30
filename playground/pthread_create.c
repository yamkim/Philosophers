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
	void		*ret;
    pid_t		pid;
 
    pid = getpid();
 
    char* thread_name = (char*)data;
    int i = 0;
 
    while (i < 3)
    {
        printf("[%s] pid:%u --- %d\n", thread_name, (unsigned int)pid, i);
        i++;
        sleep(1);
    }
	return (ret);
}
 
int main()
{
    pthread_t p_thread[2];
    int thr_id;
    int status;
    char p1[] = "thread_1";   // 1번 쓰레드 이름
    char p2[] = "thread_2";   // 2번 쓰레드 이름
    char pM[] = "thread_m";   // 메인 쓰레드 이름
 
    sleep(1);  // 2초 대기후 쓰레드 생성
 
    // ① 1번 쓰레드 생성
    // 쓰레드 생성시 함수는 t_function
    // t_function 의 매개변수로 p1 을 넘긴다.  
    thr_id = pthread_create(&p_thread[0], NULL, t_function, (void *)p1);
    if (thr_id < 0)
		handle_error();
 
    thr_id = pthread_create(&p_thread[1], NULL, t_function, (void *)p2);
    if (thr_id < 0)
		handle_error();
 
    // ③ main() 함수에서도 쓰레드에서 돌아가고 있는 동일한 함수 실행
    t_function((void *)pM);
 
    // 쓰레드 종료를 기다린다. 
    pthread_join(p_thread[0], (void **)&status);
    pthread_join(p_thread[1], (void **)&status);
 
    printf("Program is Finished\n");
 
    return 0;
}
