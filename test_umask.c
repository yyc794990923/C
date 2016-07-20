/*************************************************************************
	> File Name: test_umask.c
	> Author:yyc 
	> Mail:794990923@qq.com 
	> Created Time: 2016年07月20日 星期三 16时49分55秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
    umask(0);
    if (creat("example_681.test", S_IRWXU|S_IRWXG|S_TRWXO) < 0) {
        perror("creat");
        exit(1);
    }
    
    if (creat("example_682.test", S_IRWXU|S_IRWXG|S_TRWXO) < 0) {
        perror("creat");
        exit(1);
    }
    return 0;
}

