/*************************************************************************
	> File Name: jointhread.c
	> Author:yyc 
	> Mail:794990923@qq.com 
	> Created Time: 2016年08月01日 星期一 16时39分50秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

void assisthread(void *arg) 
{
    printf("i am helping to do some jobs\n");
    sleep(3);
    pthread_exit(0);
}

int main()
{
    pthread_t assistthid;
    int status;

    pthread_create(&assistthid, NULL, (void *)assisthread, NULL);
    pthread_join(assistthid, (void*)&status);
    printf("assistthread's exit is caused %d\n", status);

    return 0;
}
