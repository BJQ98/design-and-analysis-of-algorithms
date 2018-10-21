//
//  main.cpp
//  Huffman_code
//
//  Created by 鲍佳麒 on 2018/10/21.
//  Copyright © 2018年 鲍佳麒. All rights reserved.
//
#include<iostream>
#include<vector>
#include<string>
#include<queue>
using namespace std;
class huffman_node{//哈夫曼树的结点
    public:
        int val,id;     //权值和序列
        vector<int> id_hist;//记录当前合并结点下方所有的子结点的id，利用该id在res里面进行编码
        bool operator < (const huffman_node & other) const{       //用于优先队列排序
            if(val==other.val) return id < other.id;//按照题目要求合并后权值相等的话子树排在前面
            return val > other.val;//大的排在后面
        }
};

int main()
{
    int num,count = 1;
    cin>>num;
    for(int j = 0;j<num;j++){
        int n;
        cin>>n;
        string res[n+1];        //编码字符串
        huffman_node nd[n+1];   //输入顺序的结点排列
        priority_queue<huffman_node> min_heap;//构建最小堆
        for(int i=1,w;i<=n;i++){
            huffman_node temp;//利用temp来进行建堆
            cin>>w;
            nd[i].val = w;//保存每个结点信息
            temp.val = w;
            temp.id = i;
            temp.id_hist.push_back(i);//当前只有自己的id
            min_heap.push(temp);      //初始将每个结点视作子树b
        }
        int cur_id = n+1;//构建新的子树需要更大的id，满足题目要求排序
        while(!min_heap.empty()){
            huffman_node x = min_heap.top();
            min_heap.pop();
            if(min_heap.empty()) break;
            huffman_node y = min_heap.top();
            min_heap.pop();      //取出权值最小的两个子树
            huffman_node t;      //新的子树
            t.val = x.val + y.val;      //合并权值
            t.id = cur_id++;        //用更大的id
            for(int i=0,sz = (int)x.id_hist.size() ;i < sz ;i++){          //右子树编码
                int id = x.id_hist[i];          //找到当前结点所有的子结点
                res[id] += '1';                 //进行右子树‘1’的编码
                t.id_hist.push_back(id);         //合并y叶子结点，记录所有子叶子结点id
            }
            for(int i=0,sz = (int)y.id_hist.size();i < sz; i++){          //左子树编码
                int id = y.id_hist[i];
                res[id] += '0';
                t.id_hist.push_back(id);
            }
            min_heap.push(t);//将合并后的子树继续放入最小堆进行排序
        }
        cout<<"Case "<<count++<<endl;
        for(int i=1;i<=n;++i){
            reverse(res[i].begin(),res[i].end());//字符串需要反转
            cout<<nd[i].val<<" "<<res[i]<<endl;
        }
        cout<<endl;
    }
    return 0;
}
