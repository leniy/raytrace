/***************************************************************
 * Name:      console.cpp
 * Purpose:   光线追踪程序 命令行版本 组号012，qianwei
 * Author:    Leniy (m@leniy.info)
 * Created:   2010-09-21
 * Modify:    2010-10-26
 * Version:   0.5
 * Copyright: Leniy (http://leniy.info)
 * License:
 **************************************************************/

struct system/*系统输入参数*/
{
    int N;/*表面个数*/
    double a2; /*孔阑直径2a*/
    double w2j;/*视场大小2W，角度*/
    double w2; /*视场大小2W，弧度*/
    double lpw;/*入瞳距,物方lp*/
    int yanglishu;/*普通光线计算，L,U,H保存在后面，共yanglishu个*/
};

struct surface/*表面输入参数*/
{
    double r;/*曲率半径*/
    double d;/*到下一面的距离*/
    double nd;/*d光折射率*/
    double nF;/*F光折射率*/
    double nC;/*C光折射率*/
};

struct trace/*光线传递到某表面的参数*/
{
    double r; /*当前折射面曲率半径*/
    double d; /*当前折射面到下一折射面的距离*/
    double nw;/*当前物空间折射率*/
    double nx;/*当前像空间折射率*/
    double lw;
    double lx;
    double uw;
    double ux;
    double h;
    double iw;/*当前物空间入射角*/
    double ix;/*当前像空间出射角*/
    double PA;
};

struct astifieldcur/*像散场曲Astigmatism Field curvature*/
{
    double x;/*矢高*//*http://jpkc.zju.edu.cn/k/548/CADweb/pages/chp11.htm#轴外点沿主光线的细光束像点位置的计算*/
    double D;/*折射面间沿主光线的距离*/
    double tw;
    double tx;
    double sw;
    double sx;
};

struct normal/*任意普通光线计算*/
{
    int check;
    double L,Uj,Uh,H;/* Uj角度，U弧度。U必须输入，LH至少输入一个。check==110，表示输入LU，check==011，表示输入UH */
    double Lx,Ujx,Uhx;/*相距和像方视场角，角度°*/
};

struct plot/*存储画点数据*/
{
    double l,u,dl;
};
