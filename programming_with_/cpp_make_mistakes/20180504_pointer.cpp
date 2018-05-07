/*
 *判断更改的是指针还是指针所指向的数据
 *数组名的特定含义
 */
#include<stdio.h>
#include<iostream>
using namespace std;

void func(char *p)
{
    p=p+1;//++p;
}

int main()
{
    char s[]={'1','2','3','4',};
    func(s);
    printf("%c",*s);
    return 0;
}

