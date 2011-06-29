/***************************************************************
 * Name:      guiMain.h
 * Purpose:   光线追踪程序 GUI版本 组号012，qianwei
 * Author:    Leniy (m@leniy.info)
 * Created:   2010-09-21
 * Modify:    2010-10-26
 * Version:   0.5
 * Copyright: Leniy (http://leniy.info)
 * License:
 **************************************************************/

#ifndef GUIMAIN_H
#define GUIMAIN_H



#include "guiApp.h"


#include "GUIFrame.h"

struct systemdata/*系统输入参数*/
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
    double l,u,dl,dy;
};


class guiFrame: public GUIFrame
{
    public:
        guiFrame(wxFrame *frame);
        ~guiFrame();
    private:
        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);
        virtual void OnOpen(wxCommandEvent& event);
        virtual void OnSave(wxCommandEvent& event);
        virtual void OnRefresh(wxCommandEvent& event);
        virtual void OnCal(wxCommandEvent& event);
        virtual void OnDraw(wxCommandEvent& event);
};

class drawDlg : public DrawDlg
{
	private:
		virtual void OnClose( wxCloseEvent& event );
        virtual void OnDrawSph( wxCommandEvent& event );
	/*	virtual void OnDrawFld( wxCommandEvent& event );
		virtual void OnDrawDis( wxCommandEvent& event );*/
		virtual void OnSaveSph( wxCommandEvent& event );
/*		virtual void OnSaveFld( wxCommandEvent& event );
		virtual void OnSaveDis( wxCommandEvent& event );*/

    public:
		drawDlg(wxDialog *dialog);
		~drawDlg();

};

void raytracing(double ,double ,double ,char ,char );/*计算光线追踪，dFC各光各模式计算 */
void thinbeam(void);/*细光束像散场曲等计算*/
void currentn(char );/*根据cur_mode：'d','F','C'，设置当前物方nw和像方nx值  */

#endif // GUIMAIN_H

