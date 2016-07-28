/*************************************************************************
	> File Name: fork_g.c
	> Author:yyc 
	> Mail:794990923@qq.com 
	> Created Time: 2016年07月26日 星期二 08时35分49秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
    pid_t pid;

    pid = fork();
    switch(pid) {
        case 0:
            while(1) {
                printf("A background process ,PID: %d\n, Parent ID: %d\n", getpid(), getppid());
                sleep(3);
            }
        case -1:
            printf("process creation failed\n");
            exit(1);
        default:
            printf("I am parent process, my pid is %d\n", getpid());
            exit(0);
    }
    return 0;
}
