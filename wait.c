/*************************************************************************
	> File Name: wait.c
	> Author:yyc 
	> Mail:794990923@qq.com 
	> Created Time: 2016年07月27日 星期三 09时04分48秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
    pid_t pid;
    char *msg;
    int k;
    int exit_code;

    printf("study how to get exit code\n");
    pid = fork();
    switch(pid) {
        case 0:
            msg = "child process is running\n";
            k = 5;
            exit_code = 37;
            break;
        case -1: 
            printf("process creation failed\n");
            exit(1);
        default:
            exit_code = 0;
            break;
    }

    if (pid != 0) {
        int stat_val;
        pid_t child_pid;

        child_pid = wait(&stat_val);

        printf("child process has exit, pid  = %d\n", child_pid);
        if (WIFEXITED(stat_val)) {
            printf("child exited with code %d\n", WEXITSTATUS(stat_val));
        } else {
            printf("child exited abnormally\n");
        }
    }
    else {
        while(k-- > 0) {
            puts(msg);
            sleep(1);
        }
    }
    exit(exit_code);
}
