/*************************************************************************
	> File Name: ks.c
	> Author:yyc 
	> Mail:794990923@qq.com 
	> Created Time: 2016年06月23日 星期四 08时50分19秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct movie
{
    int number;               //影片编号
    char name[20];            //影片名称
    char director[10];        //导演
    char actor[20];           //主演
    char date[20];            //上映日期
    struct movie *next;
}movie;


void carte();


//从文件中提取数据保存到链表
movie *read_inf ()
{   
    int flag;
    movie *phead, *pend, *ptemp;
    phead = pend = (movie *)malloc(sizeof(movie));
    pend -> next = NULL;

    char filename[40];
    printf("请输入要打开的文件名:\n");
    scanf("%s", filename);
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("\n打开文件失败,按任意键退出\n");
        getchar();
        exit(1);
    }
    while (1) {
        ptemp = (movie *)malloc(sizeof(movie));
        flag = fscanf(fp, "%d %s %s %s %s\n", &ptemp -> number, ptemp -> name, ptemp -> director, ptemp -> actor, ptemp -> date);
        
        if(flag == EOF) {
            free(ptemp);
            break;
        }
        ptemp -> next = NULL;
        pend -> next = ptemp;
        pend = ptemp;
    }
    fclose(fp);
    return phead;
}




//创建链表
movie *creat()
{
    printf("---------------------------------------------\n");
    printf("          ******录入影片信息******           \n");
    printf("---------------------------------------------\n");


    char choose;
    int icount = 0;
    movie *phead, *pnew, *pend;
    phead = pend = (movie *)malloc(sizeof(movie));
   do
    {
        pnew = (movie *)malloc(sizeof(movie));
        printf("请输入影片编号\n");
        scanf("%d", &pnew -> number);
        printf("请输入影片名称\n");
        scanf("%s", pnew -> name);
        printf("请输入导演姓名\n");
        scanf("%s", pnew -> director);
        printf("请输入主演姓名\n");
        scanf("%s", pnew -> actor);
        printf("请输入上映日期\n");
        scanf("%s", pnew -> date);
        icount++;
        if (icount == 1) {
            pnew -> next = NULL;
            pend = pnew;
            phead -> next = pnew;
        } else {
            pnew -> next = NULL;
            pend -> next = pnew;
            pend =pnew;
        }

        printf("是否继续录入? y/n\n");
        getchar();
        scanf("%c", &choose);
    } while (choose == 'Y' || choose == 'y');
    return phead;
}




//浏览影片信息
void output ()
{
    movie *p = read_inf();
    for (p = p -> next; p != NULL; p = p -> next) {
        printf("编号   名称   导演   主演   上映时间\n");
        printf("----------------------------------------\n");
        printf("%d\t%s\t%s\t%s\t%s\n", p -> number, p -> name, p -> director, p -> actor, p -> date);
    }

    printf("已浏览全部影片，按任意键返回主菜单\n");
    getchar();
    getchar();
    carte ();
}





//添加信息模块
movie *insert (movie *phead)
{
    printf("--------------------------------------\n");
    printf("       ******添加影片信息******       \n");
    printf("--------------------------------------\n");
    

    char choose;
    movie *pnew = NULL, *pend = phead;
    if (phead == NULL) {
        printf("error, 按任意键退出\n");
        getchar();
        exit(1);
    }
    while (pend -> next != NULL) {
        pend = pend -> next;
    }
   do
    {
        pnew = (movie *)malloc(sizeof(movie));
        printf("请输入影片编号\n");
        scanf("%d", &pnew -> number);
        printf("请输入影片名称\n");
        scanf("%s", pnew -> name);
        printf("请输入导演姓名\n");
        scanf("%s", pnew -> director);
        printf("请输入主演姓名\n");
        scanf("%s", pnew -> actor);
        printf("请输入上映日期\n");
        scanf("%s", pnew -> date);

        pnew -> next = NULL;
        pend -> next = pnew;
        pend = pnew;


        printf("是否继续录入? y/n\n");
        getchar();
        scanf("%c", &choose);
    } while (choose == 'Y' || choose == 'y');
    return phead;
}



//保存信息模块
void save (movie *phead)
{
    char filename[40];
    printf("请输入要保存的文件名:\n");
    scanf("%s", filename);
    movie *ptemp;
    FILE *fp = fopen(filename, "w");

    if (phead == NULL) {
        printf("error, 按任意键退出\n");
        getchar();
        exit(1);
    }
    if (fp == NULL) {
        printf("打开文件失败, 按任意键退出\n");
        getchar();
        exit(1);
    }
    ptemp = phead -> next;
    while (ptemp) {
        fprintf(fp, "%d %s %s %s %s\n", ptemp -> number, ptemp -> name, ptemp -> director, ptemp -> actor, ptemp -> date);
        ptemp = ptemp -> next;
    }
    fclose(fp);

    printf("信息已保存，按任意键返回主菜单\n");
    getchar();
    getchar();
    carte ();
}





//查询信息模块
void find_inf (movie *phead)
{
    char moviename[20];
    char choice;
    movie *p = phead -> next;

    printf("请输入要查询的影片名字:\n");
    scanf("%s", moviename);
    while (p && strcmp(p -> name, moviename)) {
        p = p -> next;
    }
    if (!p) 
    {
        printf("没有查询到该影片的信息,请检查输入\n");
        printf("是否重新输入? y/n\n");
        getchar();
        scanf("%c", &choice);
        if (choice == 'Y' || choice == 'y') {
            find_inf(phead);
        } else {
            printf("按任意键返回主菜单\n");
            getchar();
            getchar();
            carte ();
        }
    }
    else {
        printf("编号   名称   导演   主演   上映时间\n");
        printf("----------------------------------------\n");
        printf("%d\t%s\t%s\t%s\t%s\n", p -> number, p -> name, p -> director, p -> actor, p -> date);
        printf("影片信息已显示,是否继续查询? y/n\n");
        getchar();
        scanf("%c", &choice);
        if (choice == 'Y' || choice == 'y') {
            find_inf(phead);
        } else {
            printf("按任意键返回主菜单\n");
            getchar();
            getchar();
            carte ();
        }

    }
}





//删除影片信息
movie *del (movie *phead)
{
    char moviename[20];
    char choice;
    movie *p = phead -> next;
    movie *q = p;

    printf("请输入要删除的影片名:\n");
    scanf("%s", moviename);
    while (p && strcmp(p -> name, moviename)) {
        q = p;
        p = p -> next;
    }
    if (!p) 
    {
        printf("没有查询到该影片的信息,请检查输入\n");
        printf("是否重新输入? y/n\n");
        getchar();
        scanf("%c", &choice);
        if (choice == 'Y' || choice == 'y') {
            del (phead);
        }
    }
    else {
        printf("编号   名称   导演   主演   上映时间\n");
        printf("----------------------------------------\n");
        printf("%d\t%s\t%s\t%s\t%s\n", p -> number, p -> name, p -> director, p -> actor, p -> date);
        printf("是否删除此影片? y/n\n");
        getchar();
        scanf("%c", &choice);
        if (choice == 'Y' || choice == 'y') {
            if (q == p) {
                p = p -> next;
            } else {
            q -> next = p -> next;
            }
            printf("删除成功,是否继续删除? y/n\n");
            getchar();
            scanf("%c", &choice);
            if (choice == 'Y' || choice == 'y') {
                del (phead);
            } 
        }
    } 
    return phead;
}


/*
//修改信息模块
void modifymovie (movie *phead, int number)
{

}
*/


void carte ()
{
    printf("-----------------------------------------------------\n");
    printf("             欢迎使用影片信息管理系统                \n");
    printf("-----------------------------------------------------\n");
    printf("                 1--录入影片信息                     \n");
    printf("                 2--添加影片信息                     \n");
    printf("                 3--浏览影片信息                     \n");
    printf("                 4--查询影片信息                     \n");
    printf("                 5--修改影片信息                     \n");
    printf("                 6--删除影片信息                     \n");
    printf("                 7--退出                             \n");

    int choice;
    printf("请选择所需功能:\n");
    scanf("%d", &choice);
    switch (choice)
    {
        case 1: save (creat ()); break;
        case 2: save (insert (read_inf ())); break;
        case 3: output (); break;
        case 4: find_inf (read_inf ()); break;
        case 6: save (del (read_inf ())); break; 
        case 7: exit (0);
    }
}


int main()
{
    carte ();
    return 0;
}




