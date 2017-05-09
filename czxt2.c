/*************************************************************************
	> File Name: czxt2.c
	> Author: yanyuchen
	> Mail: 794990923@qq.com
	> Created Time: 2017年05月09日 星期二 17时13分47秒
 ************************************************************************/



#include <stdio.h>
#include <unistd.h>
#include <linux/types.h>
#include <signal.h>
#include <ctype.h>
#include <stdlib.h>
#define MAX_CHILD_NUMBER 10
#define SLEEP_INTERVAL 2
int proc_number = 0;
void do_something();

int main(int argc, char **argv)
{
    int child_proc_number = MAX_CHILD_NUMBER;
    pid_t child;
    pid_t pid[10] ={0};
    int ch;
    if (argc > 1){
        child_proc_number = atoi(argv[1]);
        child_proc_number = (child_proc_number > 10)? 10 : child_proc_number;
    }
    for(int i = 0; i < child_proc_number; i++){
        child = fork();
        if(child == 0){
            printf("(%d)\n",proc_number);
            proc_number = i;
            do_something();
        }
        pid[i] = child;
    }
    while((ch = getchar()) != 'q'){
        if(isdigit(ch)){
            kill(pid[ch-'0'-1], SIGTERM);
        }
    }
    kill(0,SIGTERM);
}
void do_something()
{
    for(;;){
        printf("this is process NO.%d,and its pid is %d\n",proc_number,getpid());
        sleep(SLEEP_INTERVAL);
    }
}
