/*************************************************************************
	> File Name: stat.c
	> Author:yyc 
	> Mail:794990923@qq.com 
	> Created Time: 2016年07月20日 星期三 15时06分08秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<time.h>

int main(int argc, char *argv[])
{
    struct stat buf;
    //检查参数个数
    if(argc != 2) {
        printf("input error");
        exit(0);
    }
    //获取文件属性
    if(stat(argv[1], &buf) == -1) {
        perror("stat:");
        exit(1);
    }
    //打印文件属性
    printf("device = %ld\n", buf.st_dev);
    printf("inode = %ld\n", buf.st_ino);
    printf("mode = %o\n", buf.st_mode);
    printf("number of hard links = %ld\n", buf.st_nlink);
    printf("user ID of owner = %u\n", buf.st_uid);
    printf("group ID of owner = %u\n", buf.st_gid);
    printf("device type (if inode device) = %ld\n", buf.st_rdev);
    printf("total size,in bytes = %ld\n", buf.st_size);
    printf("blocksize for filesystem I/O = %ld\n", buf.st_blksize);
    printf("number of blocks allocated = %ld\n", buf.st_blocks);
    printf("time of last access = %s\n", ctime(&buf.st_atime));
    return 0;
}
