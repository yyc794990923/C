/*************************************************************************
	> File Name: my_ls.c
	> Author:yyc
	> Mail:794990923@qq.com
	> Created Time: 2016年07月21日 星期四 14时55分56秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <time.h>
#include <linux/limits.h>

#define DEBUG


//参数处理
typedef struct parameter
{
    int       a;        //参数a
    int       l;        //参数l
    int       R;        //参数r
}par;


#define MAX_FILE_NAME 1024


void output(struct stat *buf, char *path);
void sort(char filename[MAX_FILE_NAME][NAME_MAX+1], int count);
void display_single(char *path);
void display_attribute(struct stat *buf, char *path);
void path_handle(char * path);
int file_information(char *path);
void directory_informaton(char * path);
int main(int argc, char **argv);


int getScrWidth(void)
{
    return 120;
}



//参数作为全局变量，方便处理
par opt;

//最长文件名的长度
int namemax;
int Scr_length;
int filecount = 0;



typedef struct dir_queue_l
{
    char dir_name[PATH_MAX];
    struct dir_queue_l * next;
}dir_queue;

dir_queue * dir_queue_head;
dir_queue * dir_queue_end;

//队列初始化
int dir_queue_init(void)
{
    dir_queue_head = malloc(sizeof(dir_queue));
    dir_queue_head -> next = NULL;
    dir_queue_end = dir_queue_head;
    return 1;
}

//2.获取最早插入的元素并删除
//3，判断是不是空的
int dir_queue_get(char * name)
{
    dir_queue *ptemp;
    if(dir_queue_head -> next == NULL) {
	return -1;
    } else {
	ptemp = dir_queue_head -> next;
	strncpy(name, ptemp -> dir_name,PATH_MAX);
	dir_queue_head -> next = ptemp -> next;
	free(ptemp);
	return 1;
    }
}

//1,插入新元素
int dir_queue_add(char * name)
{
    dir_queue *pnew;
    pnew = malloc(sizeof(dir_queue));
    strncpy(pnew -> dir_name, name,PATH_MAX);
    pnew -> next = NULL;
    dir_queue_end -> next = pnew;
    dir_queue_end = pnew;
    return 1;
}

//排序
/*
void sort(char filename[MAX_FILE_NAME][NAME_MAX+1], int count)
{
    int i, j;
    char t[NAME_MAX+1];
    for (i = 0; i < count-1; i++) {
        for (j = 0; j < count-1-i; j++) {
            if (strcmp(filename[j], filename[j+1]) > 0) {
                strncpy(t,filename[j],strlen(filename[j]));
                strncpy(filename[j],filename[j+1],strlen(filename[j+1]));
                strncpy(filename[j+1],t,strlen(filename[j]));
            }
        }
    }
}
*/
void sort(char filename[MAX_FILE_NAME][NAME_MAX+1], int count)
{
    int i, j,min;
    char temp[NAME_MAX+1];
    for (i = 0; i < count-1; i++) {
        min = i;
        for (j = i+1; j < count; j++) {
            if (strcmp(filename[min], filename[j]) > 0) {
                min = j;
            }
        }
        if (min != i) {
            strcpy(temp, filename[i]);
            strcpy(filename[i], filename[min]);
            strcpy(filename[min], temp);
        }
    }
}

//信息输出
void output(struct stat *buf, char *path)
{

    if (opt.a == 1) {
        if (opt.l == 1) {
            display_attribute(buf, path);
        } else {
            display_single(path);
        }
    } else {
        if (path[0] != '.') {
            if (opt.l == 1) {
                display_attribute(buf, path);
            } else {
                 display_single(path);
            }
        }
    }
}

//没有参数的显示
void display_single(char *path)
{
    int i, j, len, lenth;
    lenth = Scr_length;
    i = lenth / (namemax+2);
    printf("%-s", path);
    filecount++;
    len = (namemax+2)-(strlen(path));
    for (j = 0; j < len; j++) {
	printf(" ");
    }
    if (filecount == i) {
      printf("\n");
      filecount = 0;
    }
}

//获取文件属性并打印
void display_attribute(struct stat *buf, char *path)
{
    char time[32];
    struct passwd *psd;
    struct group *grp;

    //获取并打印文件类型
    if (S_ISLNK(buf->st_mode)) {
        printf("l");
    } else if (S_ISREG(buf->st_mode)) {
        printf("-");
    } else if (S_ISDIR(buf->st_mode)) {
        printf("d");
    } else if (S_ISCHR(buf->st_mode)) {
        printf("c");
    } else if (S_ISBLK(buf->st_mode)) {
        printf("b");
    } else if (S_ISFIFO(buf->st_mode)) {
        printf("f");
    } else if (S_ISSOCK(buf->st_mode)) {
        printf("s");
    }
    //获取所有者的权限
    if (buf->st_mode & S_IRUSR) {
        printf("r");
    } else {
        printf("-");
    }
    if (buf->st_mode & S_IWUSR) {
        printf("w");
    } else {
        printf("-");
    }
    if (buf->st_mode & S_IXUSR) {
        printf("x");
    } else {
        printf("-");
    }
    //获取组权限
    if (buf->st_mode & S_IRGRP) {
        printf("r");
    } else {
        printf("-");
    }
    if (buf->st_mode & S_IWGRP) {
        printf("w");
    } else {
        printf("-");
    }
    if (buf->st_mode & S_IXGRP) {
        printf("x");
    } else {
        printf("-");
    }
    //获取其他用户权限
    if (buf->st_mode & S_IROTH) {
        printf("r");
    } else {
        printf("-");
    }
    if (buf->st_mode & S_IWOTH) {
        printf("w");
    } else {
        printf("-");
    }
    if (buf->st_mode & S_IXOTH) {
        printf("x");
    } else {
        printf("-");
    }
    printf(" ");

    printf("%5lu ", buf->st_nlink);    //打印文件连接数

    //根据uid,gid获取用户名和组名
    psd = getpwuid(buf->st_uid);
    grp = getgrgid(buf->st_gid);
    printf("%-s\t", psd -> pw_name);
    printf("%-s\t", grp -> gr_name);

    printf("%10ld ", buf->st_size);    //打印文件大小

    strcpy(time, ctime(&buf -> st_mtime));
    time[(strlen(time)) - 1] = '\0';
    printf("%s ", time);             //打印时间
    printf("%s\n", path);             //打印文件名
}

  //处理传递过来的路径文件
void path_handle(char * path)
{
    struct stat * buf;
    buf = malloc(sizeof(struct stat));
    if (lstat(path, buf) == -1) {
        fprintf(stderr,"line : %d  ", __LINE__);
        perror("lstat");
        exit(1);
    }
    if (S_ISDIR(buf->st_mode)) {
        directory_informaton(path);
    }
    if (S_ISREG(buf->st_mode)) {
        file_information(path);
    }
}

  //文件信息获取
int file_information(char *path)
{
    int flag;
    struct stat * buf;
    buf = malloc(sizeof(struct stat));
    if (lstat(path, buf) == -1) {
        fprintf(stderr,"line : %d  ", __LINE__);
        perror("lstat");
        exit(1);
    }
    if (S_ISDIR(buf->st_mode)) {
	flag = 1;
    } else {
      flag = 0;
    }
    output(buf, path);
    free(buf);
    return flag;
}

//目录信息获取
void directory_informaton(char * path)
{

    int i, count = 0;
    DIR *dir;
    struct dirent *ptr;
    char filename[1024][NAME_MAX+1];
    char work_path[PATH_MAX];
    char path_tmp[PATH_MAX];

    if ((dir = opendir(path)) == NULL) {
        fprintf(stderr,"line : %d  ", __LINE__);
        perror("opendir");
        exit(1);
    }

    //qie mulu
    
    if (chdir(path) < 0) {
        fprintf(stderr,"line : %d  ", __LINE__);
        perror("chdir");
    }
    getcwd(work_path, PATH_MAX);

    while ((ptr = readdir(dir)) != NULL) {
	int length = strlen(ptr->d_name);
    	strncpy(filename[i],ptr->d_name,length);
        i++;
        count++;
    	if (namemax < length) {
            namemax = length;
        }
    }

    sort(filename, count);
    closedir(dir);

    for(i = 0; i < count; i++) {
        //file_information(filename[i]);
	if (file_information(filename[i])&&(opt.R)) {
	    if ((strcmp(filename[i],".") == 0)||(strcmp(filename[i],"..") == 0))
		continue;
	    if ((opt.a == 0) && filename[i][0] == '.') {
		continue;
	    }
	    strcpy(path_tmp,work_path);
	    strcat(path_tmp, "/");
	    strcat(path_tmp, filename[i]);
	    //printf("%s\n", path_tmp);
	    dir_queue_add(path_tmp);
	}
    }
    
    printf("\n");
    filecount = 0;
    if (opt.R) {
	while (dir_queue_get(path_tmp) != -1)
	{
	    printf("\n%s:\n", path_tmp);
	    directory_informaton(path_tmp);
	}
    }
}

int main(int argc, char **argv)
  {
    //初始化
    int flag = 0;    //循环退出标志位
    int i;
    char * path;
    Scr_length = getScrWidth();
    char work_path[PATH_MAX];

    //参数初始化
    opt.a = 0;
    opt.l = 0;
    opt.R = 0;
    opterr = 0;    //getopt不输出错误参数
    getcwd(work_path,PATH_MAX);

    //循环处理传入参数
    while(flag != -1)
    {
        //调用getopt处理参数
        switch(getopt( argc, argv, "alR"))
        {
            case 'a':
                opt.a = 1;
                break;
            case 'l':
                opt.l = 1;
                break;
            case 'R':
                opt.R = 1;
                break;
            case '?':
                printf("出现非正常选项：%c\n",optopt);
                break;
            case -1:
                flag = -1;
                break;
            default:
                break;
        }
    }
    if (opt.R == 1) {
	dir_queue_init();
    }
    //处理参数路径部分
    if(argc == optind)
    {
        //后面不跟地址路径信息
        path = ".";
        path_handle(path);
    } else {
        //参数中包含路径信息
        for(i=optind;i<argc;i++)
        {
            path = argv[i];
	    printf("%s:\n",path);
            path_handle(path);
            if (chdir(work_path) < 0) {
                fprintf(stderr,"line : %d  ", __LINE__);
                perror("chdir");
            }
            printf("\n");
        }
    }
    return 0;
}
