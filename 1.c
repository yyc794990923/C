/*************************************************************************
	> File Name: 1.c
	> Author:yyc 
	> Mail:794990923@qq.com 
	> Created Time: 2016年06月28日 星期二 22时19分17秒
 ************************************************************************/

#include<stdio.h>

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
            } else {
                printf("按任意键返回主菜单\n");
                getchar();
