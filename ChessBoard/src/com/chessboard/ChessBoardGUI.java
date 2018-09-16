package com.chessboard;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;


public class ChessBoardGUI extends JFrame implements ActionListener{
    private int board_tile;//棋盘当前骨牌号
    private int board_size;//棋盘大小
    private int size_permit[];//允许的阶数，太大会卡
    private int x;//特殊点坐标
    private int y;
    private int L_count;
    private int L_count_local;//每次寻找的格子数量
    myChessBoard mychess;//用来获取棋盘信息
    Container con;//总容器
    JPanel jp;//格子画布
    JLabel[][] jl;//格子二维数组
    JLabel lb1,lb2,lb3;//提示输入标签
    JButton jb1,jb2;//两个按钮
    TextField text1,text2,text3;//三个输入框
    ChessBoardGUI(){ //构造函数
        super("myChessBoard");
        board_size = 0;
        board_tile = 0;
        x = 0;
        y = 0;
        size_permit = new int[]{1, 2, 4, 8, 16, 32, 64, 128};
        setDefaultCloseOperation(EXIT_ON_CLOSE);//按关闭时:退出
        setLocation(200,200);//位置
        setSize(900,900);//尺寸
        con=getContentPane();//总容器直接从JFrame获得
        jp=new JPanel();//构造新的画布
        lb1 = new JLabel("阶数");//开始组建创建和布局
        lb2 = new JLabel("x");
        lb3 = new JLabel("y");
        lb1.setBounds(10,10,30,40);
        lb2.setBounds(120,10,20,40);
        lb3.setBounds(240,10,30,40);
        jb1 = new JButton("开始");
        jb1.setBounds(400,10,120,40);
        jb1.addActionListener(this);
        jb2 = new JButton("下一步");
        jb2.setBounds(540,10,120,40);
        jb2.addActionListener(this);
        text1 = new TextField();
        text1.setBounds(50,10,50,40);
        text2 = new TextField();
        text2.setBounds(150,10,70,40);
        text3 = new TextField();
        text3.setBounds(270,10,70,40);
        con.add(lb2);
        con.add(lb3);
        con.add(lb1);
        con.add(text1);
        con.add(text2);
        con.add(text3);
        con.add(jb1);
        con.add(jb2);
        jp.setLayout(null);//空布局，自己添加位置信息
        jp.setBounds(0,50,800,800);
        con.add(jp);//加入画布
        setVisible(true);
    }
    @Override
    public void actionPerformed(ActionEvent e)//事件监听函数
    {
        String cmd = e.getActionCommand();//获取事件对应命令
        try {
            if (cmd.equals("开始")) {
                jp.removeAll();//重制画布
                board_size = size_permit[Integer.parseInt(this.text1.getText().trim())];//得到阶数对应的大小
                x = Integer.parseInt(this.text2.getText().trim());//得到特殊点坐标
                y = Integer.parseInt(this.text3.getText().trim());
                jl = new JLabel[board_size][board_size];//格子数字分配空间
                L_count = (board_size * board_size - 1) / 3;//所有格子总数
                for (int i = 0; i < board_size; i++)//初始设置白色
                    for (int j = 0; j < board_size; j++) {
                        jl[i][j] = new JLabel();
                        jl[i][j].setBounds(700 / board_size * j, 700 / board_size * i + 60,
                                700 / board_size, 700 / board_size);//此处i和j要交换，不然会显示转置后的图形
                        jl[i][j].setOpaque(true);//可见
                        jl[i][j].setBackground(Color.white);//初始为白色
                        jp.add(jl[i][j]);//加入到画布中
                    }
                board_tile = 0;
                jl[x][y].setBackground(Color.BLACK);//特殊点标记为黑色
                con.repaint();//重制画布
                con.validate();
                mychess = new myChessBoard(board_size);//每次需要运行新的算法一次
                mychess.ChessBoard(0, 0, x, y, board_size);//开始算法改变棋盘上的骨牌值
                mychess.Board[x][y] = -1;//特殊点位置骨牌号值设为-1，防止画图时候出现异常
            } else if (cmd.equals("下一步")) {
                L_count_local = 0;//已经找到的骨牌数
                for (int i = 0; i < board_size; i++) {
                    for (int j = 0; j < board_size; j++) {
                        if (mychess.Board[i][j] == board_tile)//是本次需要的骨牌
                        {
                            jl[i][j].setBackground(new Color(0xFFF8DC + board_tile * 999999));//不同颜色的生成
                            if (3 == ++L_count_local)//第三次找完了
                                break;
                        }
                    }
                }
                if(L_count != board_tile){//没找完
                    board_tile++;
                }
                else{//找完了再点击会出现弹窗提示
                    JOptionPane.showMessageDialog(null,"找完啦",
                            "提示消息",JOptionPane.PLAIN_MESSAGE);
                }
            }
        }catch(Exception ex)//总的异常处理
        {
            JOptionPane.showMessageDialog(null,"输入有误或者越界",
                    "出错了",JOptionPane.WARNING_MESSAGE);
        }
    }
}
