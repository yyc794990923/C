/*************************************************************************
	> File Name: show_files.c
	> Author:yyc 
	> Mail:794990923@qq.com 
	> Created Time: 2016年07月21日 星期四 09时09分24秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<dirent.h>

int my_readdir(char *path)
{

    DIR *dir;
    struct dirent *ptr;

    if ((dir = opendir(path)) == NULL) {
        perror("opendir");
        return -1;
    }
    while ((ptr = readdir(dir)) != NULL) {
        printf("inode = %ld\n", ptr -> d_ino);
        printf("file name = %s\n", ptr -> d_name);
    }
    closedir(dir);
    return 0;
}





int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("input error");
        exit(1);
    }
    if(my_readdir(argv[1]) < 0) {
        exit(1);
    }
    return 0;
}
