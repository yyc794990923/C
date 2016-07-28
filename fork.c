/*************************************************************************
	> File Name: fork.c
	> Author:yyc 
	> Mail:794990923@qq.com 
	> Created Time: 2016年07月25日 星期一 17时46分21秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
    pid_t pid;
    char *msg;
    int k;

    printf("process cration study\n");
    pid = fork();

    switch(pid) {
        case 0: 
                msg = "child process running";
                k = 3; 
                break;
        case -1: 
                printf("process creation fail\n"); 
                break;
        default : 
                msg = "parent process running";
                k = 5; 
                break;

    }
    while (k > 0) {
        puts(msg);
        sleep(1);
        k--;
    }
    return 0;
}
