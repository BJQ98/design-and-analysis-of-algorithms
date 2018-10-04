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
        if(dr<tr+s&&dc<tc+s) ChessBoard(tr, tc, dr, dc, s);//特殊方格在左上角
        else {//特殊方格不在左上角
            Board[tr+s-1][tc+s-1] = t;//覆盖左上角右下角
            ChessBoard(tr, tc, tr+s-1, tc+s-1, s);//覆盖左上角
        }
        if(dr<s+tr&&dc>=tc+s) ChessBoard(tr, tc+s, dr, dc, s);//特殊方格在右上角
        else {//特殊方格不在右上角
            Board[tr+s-1][tc+s]=t;//覆盖右上角左下角
            ChessBoard(tr, tc+s, tr+s-1, tc+s, s);//覆盖右上角
        }
        if(dr>=tr+s&&dc<tc+s) ChessBoard(tr+s, tc, dr, dc, s);//特殊方格在左下角
        else{//特殊方格不在左下角
            Board[tr+s][tc+s-1]=t;//覆盖左下角右上角
            ChessBoard(tr+s, tc, tr+s, tc+s-1, s);//覆盖左下角
        }
        if(dr>=tr+s&&dc>=tc+s) ChessBoard(tr+s, tc+s, dr, dc, s);//特殊方格在右下角
        else{//特殊方格不在右下角
            Board[tr+s][tc+s]=t;//覆盖右下角左上角
            ChessBoard(tr+s, tc+s, tr+s, tc+s, s);//覆盖右下角
        }
    }
    public static void main(String []args){
        new ChessBoardGUI();//打开GUI
    }
}
