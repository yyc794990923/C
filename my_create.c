/*************************************************************************
	> File Name: my_create.c
	> Author:yyc 
	> Mail:794990923@qq.com 
	> Created Time: 2016年07月18日 星期一 15时11分47秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

int main()
{
    int fd;
    if ((fd = open("example_62.c", O_CREAT|O_EXCL, S_IRUSR|S_IWUSR)) == -1) {
        //perror("open");
        printf("open:%s,    with errno:%d\n", strerror(errno), errno);
        exit(1);
    } else {
        printf("creat file success\n");
    }
    close(fd);
    return 0;
}
