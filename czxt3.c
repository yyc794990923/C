/*************************************************************************
	> File Name: czxt3.c
	> Author: yanyuchen
	> Mail: 794990923@qq.com
	> Created Time: 2017年04月17日 星期一 22时03分27秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<ctype.h>
#include<pthread.h>

#define MAX_THREAD 3 /*线程的个数*/
unsigned long long main_counter, counter[MAX_THREAD];

void* thread_worker(void*);

int main(int argc, char* argv[])
{
    int i, rtn= 0, ch;
    int x[3] = {0,1,2};
    pthread_t pthread_id[MAX_THREAD] = {0};/*存放线程id*/
    for(i = 0; i < MAX_THREAD; i++) {
        pthread_create(&pthread_id[i], NULL, thread_worker, &x[rtn++]);
    }
    do {
        unsigned long long sum = 0;
        for(i = 0; i < MAX_THREAD; i++) {
            sum += counter[i];
            printf("%llu  ",counter[i]);
        }
        printf("%llu/%llu  ", main_counter, sum);
    }while((ch = getchar()) != 'q');
    return 0;
}
void* thread_worker(void* p)
{
    int thread_num;
    thread_num = *(int *)p;
    for(;;) {
        counter[thread_num]++;
        main_counter++;
    }

}
