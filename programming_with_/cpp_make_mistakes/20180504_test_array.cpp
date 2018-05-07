/*
 *二维数组的初始化问题
 */
#include<iostream>
#include<cstdio>
using namespace std;

int main()
{
//    int a[][3];编译出错的问题是由于数组空间的总的大小并不知道。
    int a[][3]={};

    int size_a = sizeof(a);
//    cout<<a<<endl;
    printf("%d",size_a);

    return 0;
}
