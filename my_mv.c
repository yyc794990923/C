/*************************************************************************
	> File Name: my_mv.c
	> Author:yyc 
	> Mail:794990923@qq.com 
	> Created Time: 2016年07月20日 星期三 17时31分17秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("input error");
        exit(1);
    }
    if (rename(argv[1], argv[2]) == -1) {
        perror("rename");
        exit(1);
    }
    return 0;
}
