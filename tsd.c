/*************************************************************************
	> File Name: tsd.c
	> Author:yyc 
	> Mail:794990923@qq.com 
	> Created Time: 2016年08月01日 星期一 17时36分35秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>

pthread_key_t key;
 
void *thread2(void *arg)
{
    int tsd = 5;
    printf("thread %lu is running\n", pthread_self());
    pthread_setspecific (key, (void *)tsd);
    printf("thread %lu returns %d\n", pthread_self(), (int *)pthread_getspecific(key));
}

void *thread1(void *arg)
{
    int tsd = 0;
    pthread_t thid2;

    printf("thread %lu is running\n", pthread_self());
    pthread_setspecific (key, (void *)tsd);
    pthread_create(&thid2, NULL, (void *)thread2, NULL);
    sleep(5);
    printf("thread %lu returns %d\n", pthread_self(), (int *)pthread_getspecific(key));
}

int main()
{
    pthread_t thid1;
    printf("main thread begins running\n");
    pthread_key_create (&key, NULL);
    pthread_create (&thid1, NULL, (void *)thread1, NULL);
    sleep(3);
    pthread_key_delete(key);
    printf("main thread exit\n");
    pthread_exit(0);
}
