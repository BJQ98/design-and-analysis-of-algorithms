//
//  main.cpp
//  LCS
//
//  Created by 鲍佳麒 on 2018/10/5.
//  Copyright © 2018年 鲍佳麒. All rights reserved.
//

#include <iostream>
#include <string>//字符串类用于保存子序列
using namespace std;
void LCSLength(int m,int n,char *x,char *y,int **c,int **b)//子序列长度计算序列追踪函数，结果存入c和b二维数组
{
    int i,j;
    for(i=1;i<=m;i++) {c[i][0] = 0;b[i][0] = 0;}//初始化左上边界全为0
    for(i=1;i<=n;i++) {c[0][i] = 0;b[0][i] = 0;}
    for(i=1;i<=m;i++){//从1开始表示子序列长度为1开始
        for(j=1;j<=n;j++){
            if(x[i-1]==y[j-1]){//x和y数组的坐标需要对应-1，如相等说明子序列可增加长度1
                c[i][j]=c[i-1][j-1]+1;//从左上方继承下来并且加1
                b[i][j]=1;//追踪时找左上方
            }
            else if(c[i-1][j]>c[i][j-1]){//如果两个子序列上边的较大
                c[i][j]=c[i-1][j];//继承上边的值
                b[i][j]=2;//追踪时找上方
            }
            else if(c[i-1][j]<c[i][j-1]){//如果两个子序列左边的较大
                c[i][j]=c[i][j-1];//继承左边的值
                b[i][j]=3;//追踪时找左边
            }
            else{//如果两个子序列一样大，这种情况导致了多种最长子序列的产生
                c[i][j]=c[i][j-1];//继承随便哪一个
                b[i][j]=4;//追踪时左边与上方同时追踪，产生不同分支，形成多最长个子序列
            }
        }
    }
}
void LCS(int i,int j,char *x,int **b,string lcs_str){//追踪函数
    string lcs_local = lcs_str;//局部变量继承上一重的字符串
    if(i==0||j==0){//找到底了
        reverse(lcs_local.begin(),lcs_local.end());//字符串反转，因为添加的顺序是倒序的
        cout<<lcs_local<<endl;//c输出该字符串
        return;
    }
    if(b[i][j]==1){//说明该字符在最长子序列中
        lcs_local+=x[i-1];//将该字符存进局部变量中（逆序）
        LCS(i-1,j-1,x,b,lcs_local);//往左上方继续找
    }
    else if(b[i][j]==2){
        LCS(i-1, j, x, b,lcs_local);//往上方找
    }
    else if(b[i][j]==3){
        LCS(i, j-1, x, b,lcs_local);//往左边找
    }
    else{//出现分支情况
        LCS(i-1, j, x, b,lcs_local);//左边上边都要找一遍
        LCS(i, j-1, x, b,lcs_local);
    }
}
int main(int argc, const char * argv[]) {
    string lcs_str = "";//初始字符串
    int m,n;//两串字符数组的长度
    int count;//数据组数
    cin>>count;
    for(int i=0;i<count;i++){
        cin>>m>>n;
        char *x = new char[m];
        char *y = new char[n];
        for(int j=0;j<m;j++){//开始构造两个字符数组
            cin>>x[j];
        }
        for(int j=0;j<n;j++){
            cin>>y[j];
        }
        int **c = new int*[m+1];//构造两个二维数组
        int **b = new int*[m+1];
        for (int i = 0; i <= m; i++){
            c[i] = new int[n+1];
            b[i] = new int[n+1];
        }
        LCSLength(m, n, x, y, c, b);
        cout<<"Case "<<i+1<<endl;
        cout<<"最长公共子序列长度："<<c[m][n]<<endl;
        cout<<"LCS<x,y>："<<endl;
        LCS(m, n, x, b,lcs_str);
        cout<<endl;
        cout<<"c[i][j]："<<endl;
        for(int i=0;i<=m;i++){
            for(int j=0;j<=n;j++){
                cout<<c[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        cout<<"b[i][j]："<<endl;
        for(int i=0;i<=m;i++){
            for(int j=0;j<=n;j++){
                cout<<b[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    return 0;
}
