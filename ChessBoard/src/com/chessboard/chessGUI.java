package com.chessboard;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class chessGUI extends JFrame implements ActionListener{
    private int tile = 0;
    private int size = 0;
    private int x = 0;
    private int y = 0;
    int numl = 0;
    myChessBoard mychess = new myChessBoard();
    Container con;//顶层容器
    JPanel jp;//中间容器
    JLabel[][] jl;//JLabel数组
    JLabel lb1,lb2,lb3;
    JButton jb1;
    JButton jb2;
    TextField text1;
    TextField text2;
    TextField text3;
    static int n = 0;//参数，保存数组长
    chessGUI(){
        super("mychessboard");
        setDefaultCloseOperation(EXIT_ON_CLOSE);//按关闭时:退出
        setLocation(200,70);//位置
        setSize(900,900);//尺寸

        /*初始化顶层容器Container和中间容器JPanel*/
        con=getContentPane();//顶层容器直接从JFrame获得
        jp=new JPanel();//初始化一个中间容器JPanel
        jb1 = new JButton("开始");
        jb1.setBounds(400,10,120,40);
        jb1.addActionListener(this);
        jb2 = new JButton("下一步");
        jb2.setBounds(540,10,120,40);
        jb2.addActionListener(this);
        text1 = new TextField();
        lb1 = new JLabel("阶数");
        lb2 = new JLabel("x");
        lb3 = new JLabel("y");
        lb1.setBounds(10,10,30,40);
        lb2.setBounds(120,10,20,40);
        lb3.setBounds(240,10,30,40);
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
        /*布局设为空,这样JLabel才能用setBounds*/
        jp.setLayout(null);
        jp.setBounds(0,50,800,800);
        con.add(jp);
        setVisible(true);//设置可见

    }//end of构造器
    @Override
    public void actionPerformed(ActionEvent e)
    {
        System.out.println(e.getActionCommand());
        String cmd = e.getActionCommand();
        if(cmd.equals("开始")) {
            jp.removeAll();
            size = Integer.parseInt(this.text1.getText().trim());
            x = Integer.parseInt(this.text2.getText().trim());
            y = Integer.parseInt(this.text3.getText().trim());
            jl=new JLabel[size][size];
            numl = (size*size-1)/3;
            for(int i=0;i<size;i++)//初始设置白色
                for(int j=0;j<size;j++)
                {
                    jl[i][j]=new JLabel();//每个单独申请空间
                    jl[i][j].setBounds(700/size*i, 700/size*j+60, 700/size, 700/size);
                    jl[i][j].setOpaque(true);//设置非透明
                    jl[i][j].setBackground(Color.white);//白色
                    jp.add(jl[i][j]);//嵌套给中间容器JPanel
                }
            tile = 0;
            jl[x][y].setBackground(Color.BLACK);
            con.repaint();
            con.validate();
            mychess.setBoard(size);
            mychess.clearhistory();
            mychess.ChessBoard(0, 0, x, y, size);
            mychess.Board[x][y] = -1;
        }
        else if(cmd.equals("下一步")){
            int numr = 0;//记录骨牌找到几个了
            for(int i = 0;i < size;i++)
            {
                for(int j = 0;j < size;j++)
                {
                    if(mychess.Board[i][j]==tile)//如果是这次要找的
                    {
                        jl[i][j].setBackground(new Color(0x00BBBB+99999*tile));
                        //jl[i][j].setBounds(600/n*i, 600/n*j, 600/n, 600/n);
                        if(3==++numr)
                            break;
                    }
                }
                if(3==numr)
                    break;
            }
            tile++;
        }//end of for循环

    }//end of动作监听
}
