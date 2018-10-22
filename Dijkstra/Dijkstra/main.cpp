//
//  main.cpp
//  Dijkstra
//
//  Created by 鲍佳麒 on 2018/10/22.
//  Copyright © 2018年 鲍佳麒. All rights reserved.
//

#include<iostream>
#include<vector>
#include<algorithm>
#define INF 9999999//自定义最大值
using namespace std;

bool isShorter(const string &s1, const string &s2)//用于长度排序
{
    return s1.size() < s2.size();
}

void find_str(vector<vector<int>> path_list,vector<string> &str_list, int pre, string temp){//寻找所有的路径
    if(pre == -1){//找到底了
        str_list.push_back(temp);//新增一个项目
        return;
    }
    string local = temp;
    local += char(pre+'0'+1);//下标统一
    vector<int> list = path_list[pre];//准备回溯
    for(int i = 0; i<list.size();i++){
        find_str(path_list, str_list, list[i],local);//如果有一层前驱结点不止一个，遍历所有的可能性
    }
}

void Dijkstra(int **g, const int &graph_size, const int &s,const int &t){//Dijkstra算法核心
    int dist[graph_size];
    int vis[graph_size];
    for(int i = 0; i < graph_size; i++){//初始化
        dist[i] = g[s-1][i];
        vis[i] = 0;
    }
    vector<vector<int>> path_list;//用于记录每个结点的前驱结点
    for(int i = 0; i < graph_size; i++){
        if(dist[i] < INF && dist[i] != -1){//可达，前驱结点记为起点
            path_list.push_back(vector<int> (1, s-1));
        }
        else{//不可达，前驱结点记为-1
            path_list.push_back(vector<int> (1,-1));
        }
    }
    dist[s-1] = 0;//起始点到自己距离为0，其实在程序中无用
    vis[s-1] = 1;//标记起始点已被访问
    for(int i = 0; i < graph_size; i++){
        int temp = INF;
        int u = s-1;
        for(int j = 0; j < graph_size; j++){//找到未被访问的距离起始点最近的结点
            if(!vis[j]&&(dist[j] < temp)){
                u = j;
                temp = dist[j];
            }
        }
        vis[u] = 1;//访问它
        for(int j = 0; j <graph_size; j++){
            if(!vis[j]&&(g[u][j] < INF)){//没被访问且可达
                int newdist = dist[u] + g[u][j];//新的路长
                if(newdist < dist[j]){//如果比原来的小，说明要更新路径
                    dist[j] = newdist;
                    path_list[j].clear();//清空以前的前驱
                    path_list[j].push_back(u);//加入现在的前驱
                }
                else if(newdist == dist[j]){//出现分支情况
                    path_list[j].push_back(u);//一层存放多个前驱结点
                }
            }
        }
    }
    vector<string> res;//结果字符串容器
    string temp = "";//初始化递归局部变量
    find_str(path_list, res, t-1, temp);//寻找所有的可能性，返回更改后的字符串容器
    for(int j=0;j<res.size();j++){
        reverse(res[j].begin(), res[j].end());//路径是反的，需要反转
    }
    sort(res.begin(), res.end(), isShorter);//根据长短和字典序排序
    cout<<"The least distance from "<<s<<"->"<<t<<" is "<<dist[t-1]<<endl;//格式输出
    cout<<"the path is ";
    for(int i = 0; i < res[0].length(); i++){
        if(i!=res[0].length()-1){
            cout<<res[0][i]<<"->";
        }
        else{
            cout<<res[0][i];
        }
    }
    cout<<endl;
}


int main(int argc, const char * argv[]) {
    int graph_size;
    int count = 0;
    while(cin>>graph_size){
        int **g = new int*[graph_size];
        int s,t;
        for (int i = 0; i < graph_size; i++){//给二维数组分配空间
            g[i] = new int[graph_size];
        }
        for(int i = 0; i < graph_size; i++){
            for(int j = 0; j < graph_size; j++){
                cin>>g[i][j];
                if(g[i][j] == -1 && i!=j){
                    g[i][j] = INF;
                }
            }
        }
        cin>>s>>t;
        cout<<"Case "<<++count<<endl;
        Dijkstra(g, graph_size, s, t);
        for (int i = 0; i < graph_size; i++){//释放空间，防止内存泄漏
            delete[] g[i];
        }
        delete[]g;
    }
    return 0;
}
