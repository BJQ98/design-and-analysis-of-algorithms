package com.chessboard;


public class myChessBoard{//算法核心类
    public  int Board[][];//棋盘二维数组
    private int tile;//骨牌号，用于递归
    myChessBoard(int size){//构造函数
        Board = new int[size][size];
        tile = 0;
    }
    public void ChessBoard(int tr,int tc, int dr,int dc,int size){//参考书上代码
        if(size == 1) return;
        int t = tile++,s = size/2;
        if(dr<tr+s&&dc<tc+s) ChessBoard(tr, tc, dr, dc, s);
        else {
            Board[tr+s-1][tc+s-1] = t;
            ChessBoard(tr, tc, tr+s-1, tc+s-1, s);
        }
        if(dr<s+tr&&dc>=tc+s) ChessBoard(tr, tc+s, dr, dc, s);
        else {
            Board[tr+s-1][tc+s]=t;
            ChessBoard(tr, tc+s, tr+s-1, tc+s, s);
        }
        if(dr>=tr+s&&dc<tc+s) ChessBoard(tr+s, tc, dr, dc, s);
        else{
            Board[tr+s][tc+s-1]=t;
            ChessBoard(tr+s, tc, tr+s, tc+s-1, s);
        }
        if(dr>=tr+s&&dc>=tc+s) ChessBoard(tr+s, tc+s, dr, dc, s);
        else{
            Board[tr+s][tc+s]=t;
            ChessBoard(tr+s, tc+s, tr+s, tc+s, s);
        }
    }
    public static void main(String []args){
        new ChessBoardGUI();//打开GUI
    }
}
