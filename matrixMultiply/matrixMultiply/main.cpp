//
//  main.cpp
//  matrixMultiply
//
//  Created by 鲍佳麒 on 2018/9/24.
//  Copyright © 2018年 鲍佳麒. All rights reserved.
//

#include <iostream>
using namespace std;
void MatrixChain(int p[], int **m, int **s, int n)
{
    //将对角线元素赋值为零，即单个矩阵计算量为0
    for (int i = 0; i < n; i++) m[i][i] = 0;
    //r是矩阵相乘个数
    for (int r = 2; r <= n; r++){
        for (int i = 0; i <= n - r; i++)
        {
            int j = i + r - 1;
            //计算A[i, j] = A[i: i] A[i+1: j]
            m[i][j] = m[i + 1][j] + p[i] * p[i + 1] * p[j + 1];
            s[i][j] = i;  //记下断点i
            for (int k = i + 1; k < j; k++)
            {
                //对i<k<j, 逐个计算A[i, j] = A[i: k] A[k+1: j]
                int t = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                //记下较小的m[i][j]及相应的断点k
                if (t < m[i][j])
                {
                    m[i][j] = t;  s[i][j] = k;
                }
            }
        }
    }
}

//找出s数组中记录的最优断开点
void Traceback(int i, int j, int **s,int &count)
{
    if (i == j)
    {
        cout << "A" << i + 1;
        return;
    }
    int _count=count;
    count++;
    if(_count!=0){
        cout << "(";
    }
    Traceback(i, s[i][j], s,count);
    Traceback(s[i][j] + 1, j, s,count);
    if(_count!=0){
        cout << ")";
    }
}

int main() {
    int in_num;
    cin>>in_num;
    const int n = in_num;
    int count=0;
    int *p = new int[n+1];
    for(int i=0;i<=n;i++){
        cin>>p[i];
    }
    int **m = new int*[n];
    int **s = new int*[n];
    for (int i = 0; i < n; i++){
        m[i] = new int[n];
        s[i] = new int[n];
    }
    MatrixChain(p, m, s, n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<m[i][j]<<" ";
        }
        cout<<endl;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<s[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<m[0][n-1]<<endl;
    Traceback(0, n - 1, s,count);
    for (int i = 0; i < n; i++){
        delete[] m[i];
        delete[] s[i];
    }
    delete[]m;
    delete[]s;
    delete[]p;
    return 0;
}
