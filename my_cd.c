/*************************************************************************
	> File Name: my_cd.c
	> Author:yyc 
	> Mail:794990923@qq.com 
	> Created Time: 2016年07月20日 星期三 22时01分29秒
 ************************************************************************/

#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<stdlib.h>
#include<linux/limits.h>
//#include<sys/types.h>
//#include<sys/stat.h>
//#include<fcntl.h>

int main(int argc, char **argv)
{
    char buf[PATH_MAX +1];

    if (argc < 2) {
        printf("input error");
    }
    
    if (chdir(argv[1]) == -1) {
        perror("chdir");
        exit(1);
    }
    
    if (getcwd(buf, 512)  == NULL) {
        perror("getcwd");
        exit(1);
    }
    
   /* if (creat("example", S_IRWXU) == -1) {
        perror("creat");
        exit(1);
    }
   */
    printf("%s\n",buf);
    return 0;
}
