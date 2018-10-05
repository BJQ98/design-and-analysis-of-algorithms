//
//  main.cpp
//  matrixMultiply
//
//  Created by 鲍佳麒 on 2018/9/24.
//  Copyright © 2018年 鲍佳麒. All rights reserved.
//

#include <iostream>
using namespace std;
void MatrixChain(int *p, int **m, int **s, int n)
{
    //单个矩阵计算量为0
    for (int i = 1; i <= n; i++) {
        m[i][i] = 0;
    }
    //r是相乘矩阵的个数
    for (int r = 2; r <= n; r++){
        for (int i = 1; i <= n - r + 1; i++)
        {
            int j = i + r - 1;//j为右边界
            m[i][j] = m[i + 1][j] + p[i-1] * p[i] * p[j];//初始化为最左边的矩阵与右边一堆矩阵相乘的结果矩阵相乘
            s[i][j] = i;  //记下断点位置i，断点断在i的后方
            for (int k = i + 1; k < j; k++){//寻找最优子结构
                int t = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];//从两端边界中间开始寻找最佳断点位置
                if (t < m[i][j]){
                    m[i][j] = t;  s[i][j] = k;//比初始化的运算次数更少，选择此处作为断点
                }
            }
        }
    }
}

//找出s数组中记录的最优断开点
void Traceback(int i, int j, int **s,int &count)
{
    if (i == j){//递归出口
        cout << "A" << i;
        return;
    }
    int _count=count;//局部变量，用于过滤最外边的括号
    count++;
    if(_count!=0){//最外层括号不加
        cout << "(";//子结构左边界
    }
    Traceback(i, s[i][j], s,count);//追踪当前断点左侧最优断点结构
    Traceback(s[i][j] + 1, j, s,count);//追踪当前断点右侧最优断点结构
    if(_count!=0){
        cout << ")";//子结构右边界
    }
}

int main() {
    int in_num;//输入的矩阵相乘数
    int count = 1;
    while(cin>>in_num){
        const int n = in_num;//将输入的数看成常数，用于数组定义
        int Trace_count=0;
        int *p = new int[n+1];//矩阵规模数组
        for(int i=0;i<=n;i++){
            cin>>p[i];//输入矩阵规模
        }
        int **m = new int*[n+1];//矩阵乘法次数记录二维数组
        int **s = new int*[n+1];//矩阵断点位置记录二维数组
        for (int i = 0; i <= n; i++){//给二维数组分配空间
            m[i] = new int[n+1];
            s[i] = new int[n+1];
        }
        MatrixChain(p, m, s, n);//进行矩阵连乘运算
        cout<<"Case "<<count++<<endl;
        cout<<m[1][n]<<" ";//最少乘法次数
        Traceback(1, n, s, Trace_count);//追踪断点位置
        cout<<endl;
        for (int i = 0; i <= n; i++){//释放空间，防止内存泄漏
            delete[] m[i];
            delete[] s[i];
        }
        delete[]m;
        delete[]s;
        delete[]p;
    }
    return 0;
}
