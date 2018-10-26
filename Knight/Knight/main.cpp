//
//  main.cpp
//  Knight
//
//  Created by 鲍佳麒 on 2018/10/26.
//  Copyright © 2018年 鲍佳麒. All rights reserved.
//

#include <iostream>
#include <queue>
#include <string>
#define INF 999999
using namespace std;
int board[9][9];//bfs用
bool vis[9][9];//回溯用
int dir[8][2]={{-1,2},{-2,1},{2,1},{1,2},{-1,-2},{-2,-1},{2,-1},{1,-2}};//八个方向
int min_step = INF;
struct K{
    int x,y;
};//Knight结构体，入队用
K s1,s2;
int bfs(int x1,int y1,int x2,int y2){//广度优先遍历
    queue<K> Q;
    s1.x=x1;
    s1.y=y1;
    Q.push(s1);
    while(!Q.empty()){
        s1=Q.front();
        Q.pop();
        for(int i=0;i<8;i++){
            int end_x=s1.x+dir[i][0];
            int end_y=s1.y+dir[i][1];
            if(end_x<=8 && end_x>=1 && end_y<=8&& end_y>=1){
                s2.x=end_x;
                s2.y=end_y;
                if(board[s1.x][s1.y]+1<board[end_x][end_y]){
                    board[end_x][end_y]=board[s1.x][s1.y]+1;
                    if(end_x==x2&&end_y==y2){
                        return board[x2][y2];
                    }
                    Q.push(s2);
                }
            }
        }
    }
    return board[x2][y2];
}

void Backtrack(int steps,int x1,int y1,const int &x2,const int &y2){//回溯法
    if(steps > min_step) return;//直接剪枝
    if(x1==x2 && y1==y2){//找到终点
        if(steps<min_step){
            min_step=steps;//更新最短路
        }
        return;
    }
    for(int i=0;i<8;i++){//八个方向
        int end_x=x1+dir[i][0];
        int end_y=y1+dir[i][1];
        if(end_x<=8 && end_x>=1 && end_y<=8&& end_y>=1 && !vis[end_x][end_y]){//排列树
            vis[end_x][end_y]=true;
            Backtrack(steps+1,end_x,end_y,x2,y2);
            vis[end_x][end_y]=false;
        }
    }
}

int main(int argc, const char * argv[]) {
    string start,end;
    int start_x,start_y,end_x,end_y;
    while(cin>>start>>end){
        min_step = INF;
        for(int i=0;i<=8;i++){
            for(int j=0;j<=8;j++){
                board[i][j]=INF;
            }
        }
        for(int i=0;i<=8;i++){
            for(int j=0;j<=8;j++){
                vis[i][j]=false;
            }
        }
        start_x = start[0] - 'a' + 1;
        start_y = start[1] - '0';
        end_x = end[0] - 'a' + 1;
        end_y = end[1] - '0';
        board[start_x][start_y]=0;
        vis[start_x][start_y]=true;
        Backtrack(0,start_x,start_y,end_x,end_y);
        cout<<start<<"==>"<<end<<": "<<min_step<<" moves"<<endl;
    }
    return 0;
}
