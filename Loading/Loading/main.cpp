//
//  main.cpp
//  Loading
//
//  Created by 鲍佳麒 on 2018/10/27.
//  Copyright © 2018年 鲍佳麒. All rights reserved.
//

#include <iostream>
using namespace std;
class Loading{
    friend int MaxLoading(int [], int ,int ,int []);
private:
    void Findbestw(int i);
    void Backtrack(int i, bool &flag);
    int n,          //集装箱数
        * x,        //当前解
        * bestx;    //当前最优解
    int *w,         //集装箱重量数组
        c,          //第一艘轮船的载重量
        cw,         //当前载重量
        bestw,      //当前最优载重量
        r;          //剩余集装箱重量
};

void Loading::Backtrack(int i,bool &flag)
{
    if(flag){
        if(i > n){
            if(cw == bestw){
                for(int j = 1;j <= n;j++){//只更新一次
                    bestx[j] = x[j];
                }
                flag = false;
            }
            return;
        }
        r -= w[i];
        if(cw + w[i] <= c){//左子树
            x[i] = 1;//左方向
            cw += w[i];
            Backtrack(i+1, flag);
            cw -= w[i];//准备进入右方向
        }
        x[i] = 0;//因为字典序，所以解空间的树叉越往左越好，无条件进入右子树
        Backtrack(i+1, flag);
        r += w[i];
    }
}
void Loading::Findbestw(int i)
{
    if(i > n){
        if(cw > bestw){
            bestw = cw;
        }
        return;
    }
    r -= w[i];
    if(cw + w[i] <= c){
        cw += w[i];
        Findbestw(i+1);
        cw -= w[i];
    }
    if(cw + r > bestw){
        Findbestw(i+1);
    }
    r += w[i];
}

int MaxLoading(int w[],int c,int n,int bestx[])
{
    Loading X;
    X.x = new int[n+1];
    X.w = w;
    X.c = c;
    X.n = n;
    X.bestx = bestx;
    X.bestw = 0;
    X.cw = 0;
    for(int i=1;i <= n;i++){
        X.r += w[i];
    }
    bool flag = true;
    X.Findbestw(1);//先找到bsetw
    X.Backtrack(1,flag);//采取书后第一种改进算法才能选择字典序大的选择方案，并且限制复杂度在O(2^n)
    delete[]X.x;
    return X.bestw;
}

int main(int argc, const char * argv[]) {
    int num;
    int *weight;
    int *x;
    int s1,s2;
    int count = 0;
    while(cin>>num){
        int sum = 0;
        weight = new int[num+1];
        x = new int[num+1]{0};
        for(int i=1;i<=num;i++){
            cin>>weight[i];
        }
        cin>>s1>>s2;
        int best = MaxLoading(weight, s1, num, x);
        for(int i=1;i<=num;i++){
            sum += weight[i];
        }
        cout<<"Case "<<++count<<endl;
        if(sum - best <= s2){//有解
            cout<<best<<endl;
            for(int i=1;i<=num;i++){
                cout<<x[i];
            }
            cout<<endl;
        }
        else{//无解
            cout<<"No"<<endl;
        }
    }
    return 0;
}
