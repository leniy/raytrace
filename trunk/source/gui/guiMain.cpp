/***************************************************************
 * Name:      guiMain.cpp
 * Purpose:   光线追踪程序 GUI版本 组号012，qianwei
 * Author:    Leniy (m@leniy.info)
 * Created:   2010-09-21
 * Modify:    2010-10-26
 * Version:   0.5
 * Copyright: Leniy (http://leniy.info)
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "guiMain.h"
#include <wx/msgdlg.h>
#include <wx/filedlg.h>
#include <string>
#include "wx/wx.h"

#include <stdlib.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <cmath>
#include <wx/textfile.h>
#include <wx/choicdlg.h>

using namespace std;

#define MAX (201)    /*最多表面数200,0号为最前面的空气*/
#define INF (1e200)   /*无穷远*/

systemdata sys;
surface len[MAX];/*1~N为输入数据，0号dFC设置为1，为空气*/
trace temp[MAX];/*temp[MAX]用于存放各次计算的结果*/
astifieldcur afc[MAX];
normal putong[MAX];
wxString file;
string output_str="";
char output_temp[100];

/** 基本待求参数 **/
double cal_f,cal_l,cal_lp,cal_y0,cal_dlm,cal_xt,cal_xs,cal_Dxts,cal_Dy;
/*       f'   l'     lp'    y0'    δlm'    xt'   xs'     Δxts'   Δy'  */

/** 其他变量 **/
double cal_lt,cal_ls;
plot plot_sph_dFC[3][101],plot_fld_dFC[3][101],plot_dis_dFC[3][101];
char plot_ch[3]={'d','F','C'};
wxPen penblack(*wxBLACK,1);
wxPen pend(*wxGREEN,1);
wxPen penF(*wxBLUE,1);
wxPen penC(*wxRED,1);

guiFrame::guiFrame(wxFrame *frame)
    : GUIFrame(frame)
{
    statusBar->SetStatusText(_("2010/9/21 by leniy"), 0);
    statusBar->SetStatusText(_("欢迎"), 1);
}

guiFrame::~guiFrame()
{
}

void guiFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void guiFrame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void guiFrame::OnAbout(wxCommandEvent &event)
{
    wxString msg = wxT("\
/***************************************************************\n\
 * Name:      光线追踪BETA\n\
 * Purpose:   光线追踪程序 GUI版本 组号012，qianwei\n\
 * Author:    Leniy (m@leniy.info)\n\
 * Created:   2010-09-21\n\
 * Modify:    2010-10-26\n\
 * Version:   0.5\n\
 * Copyright: Leniy (http://leniy.info)\n\
 * License:\n\
 **************************************************************/\n\
\n\
    目前实现功能：\n\
    1. 任意Sequential Mode 球面镜头组基本参数计算\n\
    2. 任意输入光线跟踪计算输出\n\
    3. 各色光球差曲线绘制\n\
    4. etc");
    wxMessageBox(msg, _("关于"));
}

void guiFrame::OnSave(wxCommandEvent &event)
{
    wxFileDialog savdlg(this, _("保存镜头参数"), _(""), _(""), _("word 2003(*.doc)|*.doc"),  wxFD_SAVE, wxDefaultPosition);
    if(savdlg.ShowModal()!=wxID_OK) return;
    file.Clear();
    file=savdlg.GetPath();
    char filesave[100];/*存储打开的文件名*/
    strncpy(filesave, (const char*)file.mb_str(wxConvLocal), 99);
    FILE *savfilep;
    savfilep=fopen(filesave,"w");
    fprintf(savfilep,output_str.c_str());
    fclose(savfilep);
}

void guiFrame::OnOpen(wxCommandEvent &event)
{
    wxFileDialog fdlog(this, _("打开镜头文件"), _(""), _(""), _("镜头数据文件(*.dat)|*.dat"),  wxFD_OPEN, wxDefaultPosition);
    if(fdlog.ShowModal()!=wxID_OK) return;
    file.Clear();
    file=fdlog.GetPath();
    char fileopen[100];/*存储打开的文件名*/
    strncpy(fileopen, (const char*)file.mb_str(wxConvLocal), 99);
    statusBar->SetStatusText(file, 1);
    statusBar->SetStatusText(_("2010/9/21 by leniy"), 0);
    int i;
    FILE *fp;
    fp=fopen(fileopen,"r");
    fscanf(fp,"%d,%le,%le,%le,%d\n\n",&sys.N,&sys.lpw,&sys.a2,&sys.w2j,&sys.yanglishu);
    sys.w2=sys.w2j/180.0*3.141592654;
    for(i=1;i<=sys.N;i++) fscanf(fp,"%le,%le,%le,%le,%le\n",&len[i].r,&len[i].d,&len[i].nd,&len[i].nF,&len[i].nC);
    fscanf(fp,"\n");
    for(i=1;i<=sys.yanglishu;i++)
    {
        fscanf(fp,"%le,%le,%le\n",&putong[i].L,&putong[i].Uj,&putong[i].H);
    }
    fclose(fp);
    len[0].r=len[0].d=len[0].nd=len[0].nF=len[0].nC=1;/*最前面的空气,或物面,直接赋值{1,1,1,1,1}会提示-std=c++0x限制*/

    wxString wxdat;
    wxdat << sys.N;
	sys_data->SetCellValue(0,0,wxdat);
	wxdat.clear();
    wxdat << sys.lpw;
	sys_data->SetCellValue(0,1,wxdat);
    wxdat.clear();
    wxdat << sys.a2;
	sys_data->SetCellValue(0,2,wxdat);
    wxdat.clear();
    wxdat << sys.w2j;
	sys_data->SetCellValue(0,3,wxdat);
    wxdat.clear();
    wxdat << sys.yanglishu;
	sys_data->SetCellValue(0,4,wxdat);
    wxdat.clear();

    if(sys.N>3)len_data->InsertRows(0,sys.N-3,1);

    for(i=0;i<=sys.N;i++)
    {
        wxdat << len[i].r;
        len_data->SetCellValue(i,0,wxdat);
        wxdat.clear();
        wxdat << len[i].d;
        len_data->SetCellValue(i,1,wxdat);
        wxdat.clear();
        wxdat << len[i].nd;
        len_data->SetCellValue(i,2,wxdat);
        wxdat.clear();
        wxdat << len[i].nF;
        len_data->SetCellValue(i,3,wxdat);
        wxdat.clear();
        wxdat << len[i].nC;
        len_data->SetCellValue(i,4,wxdat);
        wxdat.clear();
    }
    len_data->SetCellValue(0,0,_("无"));
    len_data->SetCellValue(0,1,_("无"));

    if(sys.yanglishu>4)putong_data->InsertRows(0,sys.yanglishu-4,1);

    for(i=1;i<=sys.yanglishu;i++)
    {
        wxdat << putong[i].L;
        putong_data->SetCellValue(i-1,0,wxdat);
        wxdat.clear();
        wxdat << putong[i].Uj;
        putong_data->SetCellValue(i-1,1,wxdat);
        wxdat.clear();
        wxdat << putong[i].H;
        putong_data->SetCellValue(i-1,2,wxdat);
        wxdat.clear();
    }
}

void guiFrame::OnRefresh(wxCommandEvent &event)
{
    wxString msg = wxT("文件打开时已自动调用刷新");
    wxMessageBox(msg, _("刷新"));
}

void guiFrame::OnCal(wxCommandEvent &event)
{
    output_str="";
    sprintf(output_temp,"\n/******************* 任务书要求的9个数据 *******************/\n\n");output_str+=output_temp;

    trace para_1;/*第一近轴光*/
    raytracing(INF,0,sys.a2/2,'d','P');para_1=temp[sys.N];/*d光第一近轴*/
    cal_f=(sys.a2/2)/para_1.ux;
    cal_l=para_1.lx;
    sprintf(output_temp,"理想焦距   f'=%3.8f\n高斯像距   l'=%3.8f\n",cal_f,cal_l);output_str+=output_temp;

    trace para_2;/*第二近轴光*/
    raytracing(sys.lpw,-sys.w2/2,0,'d','P');para_2=temp[sys.N];/*d光第二近轴*/
    cal_lp=para_2.lx;
    cal_y0=(cal_lp-cal_l)*tan(para_2.ux);
    sprintf(output_temp,"出瞳距    lp'=%3.8f\n像高      y0'= %3.8f\n",cal_lp,cal_y0);output_str+=output_temp;

    trace meri_zsdby;/*子午面轴上点边缘光线*/
    raytracing(INF,0,sys.a2/2,'d','M');meri_zsdby=temp[sys.N];/*子午面轴上点d光边缘光线*/
    cal_dlm=meri_zsdby.lx-cal_l;
    sprintf(output_temp,"轴向球差δLm'=%3.8f\n",cal_dlm);output_str+=output_temp;

    thinbeam();/*细光束像散场曲等计算*/
    sprintf(output_temp,"子午场曲  xt'=%3.8f\n",cal_xt);output_str+=output_temp;
    sprintf(output_temp,"弧矢场曲  xs'=%3.8f\n",cal_xs);output_str+=output_temp;
    sprintf(output_temp,"像散   Δxts'=%3.8f\n",cal_Dxts);output_str+=output_temp;

    trace meri_zwdz;/*子午面轴外点主光线*/
    raytracing(0,-sys.w2/2,0,'d','M');meri_zwdz=temp[sys.N];/*子午面轴外点d光主光线*/
    double zwdlp=meri_zwdz.lx,zwdup=meri_zwdz.ux,zwdyp=(zwdlp-cal_l)*tan(zwdup);
    cal_Dy=(zwdyp-cal_y0)/cal_y0;
    sprintf(output_temp,"相对畸变 Δy'=%3.8f\n",cal_Dy);output_str+=output_temp;

    sprintf(output_temp,"\n/*******************      其它参数       *******************/\n\n");output_str+=output_temp;

    raytracing(INF,0,0.707*sys.a2/2,'d','M');/*子午面轴上点d光0.707带光*/
    sprintf(output_temp,"0.707带光最大剩余球差δLmax'=%3.8f\n",temp[sys.N].lx-cal_l);output_str+=output_temp;

    sprintf(output_temp,"垂轴球差δTm'=%3.8f\n",cal_dlm*tan(meri_zsdby.ux));output_str+=output_temp;
    sprintf(output_temp,"线性畸变 δy'=%3.8f\n",zwdyp-cal_y0);output_str+=output_temp;
    sprintf(output_temp,"实际像高  yp'= %3.8f\n",zwdyp);output_str+=output_temp;

    trace meri_zwds;/*子午面轴外点上光线*/
    raytracing(sys.a2/2/tan(-sys.w2/2),-sys.w2/2,sys.a2/2,'d','M');meri_zwds=temp[sys.N];/*子午面轴外点d光上光线*/
    double zwdla=meri_zwds.lx,zwdua=meri_zwds.ux,zwdya=(zwdla-cal_l)*tan(zwdua);
    trace meri_zwdx;/*子午面轴外点下光线*/
    raytracing(-sys.a2/2/tan(-sys.w2/2),-sys.w2/2,-sys.a2/2,'d','M');meri_zwdx=temp[sys.N];/*子午面轴外点d光下光线*/
    double zwdlb=meri_zwdx.lx,zwdub=meri_zwdx.ux,zwdyb=(zwdlb-cal_l)*tan(zwdub);
    double cal_Kt=(zwdya+zwdyb)/2-zwdyp;
    sprintf(output_temp,"子午彗差  Kt'= %3.8f\n",cal_Kt);output_str+=output_temp;

    trace meri_zwdzF;/*子午面轴外点F光主光线*/
    raytracing(0,-sys.w2/2,0,'F','M');meri_zwdzF=temp[sys.N];/*子午面轴外点F光主光线*/
    double zwdlF=meri_zwdzF.lx,zwduF=meri_zwdzF.ux,zwdyF=(zwdlF-cal_l)*tan(zwduF);
    trace meri_zwdzC;/*子午面轴外点C光主光线*/
    raytracing(0,-sys.w2/2,0,'C','M');meri_zwdzC=temp[sys.N];/*子午面轴外点C光主光线*/
    double zwdlC=meri_zwdzC.lx,zwduC=meri_zwdzC.ux,zwdyC=(zwdlC-cal_l)*tan(zwduC);
    sprintf(output_temp,"d光实际像高y'= %3.8f\n",zwdyp);output_str+=output_temp;
    sprintf(output_temp,"F光实际像高y'= %3.8f\n",zwdyF);output_str+=output_temp;
    sprintf(output_temp,"C光实际像高y'= %3.8f\n",zwdyC);output_str+=output_temp;
    sprintf(output_temp,"倍率色差δych'=%3.8f\n",zwdyF-zwdyC);output_str+=output_temp;
    sprintf(output_temp,"位置色差δlch'=%3.8f\n",zwdlF-zwdlC);output_str+=output_temp;

    double cal_F=(sys.a2/2)/sin(meri_zsdby.ux);
    double cal_df=cal_F-cal_f;
    double cal_OSC=cal_df/cal_f-cal_dlm/(cal_l-cal_lp);/*初级正弦差*/
    sprintf(output_temp,"初级正弦差OSC= %3.8f\n",cal_OSC);output_str+=output_temp;
    double cal_Ks=cal_y0*cal_OSC;
    sprintf(output_temp,"弧矢彗差  Ks'= %3.8f\n",cal_Ks);output_str+=output_temp;

    sprintf(output_temp,"d光轴上全孔径球差%3.8f\n",meri_zsdby.lx-para_1.lx);output_str+=output_temp;

sprintf(output_temp,"\n/*******************     任意普通光线    *******************/\n\n");output_str+=output_temp;

    for(int i=1;i<=sys.yanglishu;i++)
    {
        raytracing(putong[i].L,putong[i].Uh,putong[i].H,'d','M');
        putong[i].Lx=temp[i].lx;putong[i].Uhx=temp[i].ux;putong[i].Ujx=putong[i].Uhx/3.141592654*180;
        sprintf(output_temp,"输入：L=%.4e U=%.4f H=%.4e \n                    输出：L'=%.4e U'=%.4e\n\n",putong[i].L,putong[i].Uj,putong[i].H,putong[i].Lx,putong[i].Ujx);output_str+=output_temp;
    }

    wxString qqqqq(output_str.c_str(), wxConvUTF8);
    wxMessageBox(qqqqq, _("参数"));
}

void guiFrame::OnDraw(wxCommandEvent &event)
{
    drawDlg *dlg = new drawDlg(NULL);
    dlg->Show();
}

drawDlg::drawDlg(wxDialog *dialog)
    : DrawDlg(dialog)
{
}

void drawDlg::OnClose(wxCloseEvent &event)
{
    Destroy();
}

drawDlg::~drawDlg()
{
}

void drawDlg::OnDrawSph(wxCommandEvent &event)
{
    /*球差,dFC*/
    for(int i=1;i<=100;i++)
    {
        for(int j=0;j<3;j++)
        {
            raytracing(INF,0,i/100.0*sys.a2/2,plot_ch[j],'M');
            plot_sph_dFC[j][i].l=temp[sys.N].lx;
            plot_sph_dFC[j][i].dl=plot_sph_dFC[j][i].l-cal_l;
        }
    }

    wxClientDC dc(this);

    dc.SetPen(penblack);
    dc.DrawText(_("球差"),wxPoint(50 ,50));
    for(int i=1;i<=400;i++)
        for(int j=-1;j<=1;j++){
            dc.DrawPoint(wxPoint(200+j,i));
            dc.DrawPoint(wxPoint(i,400+j));
    }

    dc.SetPen(pend);
    for(int i=1;i<=100;i++)for(int x=-2;x<=2;x++)for(int y=-2;y<=2;y++)
        dc.DrawPoint(wxPoint((int)(plot_sph_dFC[0][i].dl/0.0005+200+x),((101-i)*4)+y));
    dc.SetPen(penF);
    for(int i=1;i<=100;i++)for(int x=-2;x<=2;x++)for(int y=-2;y<=2;y++)
        dc.DrawPoint(wxPoint((int)(plot_sph_dFC[1][i].dl/0.0005+200+x),((101-i)*4)+y));
    dc.SetPen(penC);
    for(int i=1;i<=100;i++)for(int x=-2;x<=2;x++)for(int y=-2;y<=2;y++)
        dc.DrawPoint(wxPoint((int)(plot_sph_dFC[2][i].dl/0.0005+200+x),((101-i)*4)+y));

    dc.SetPen((wxNullPen));
}

void drawDlg::OnSaveSph(wxCommandEvent &event)
{
        if(wxMessageBox(_("是否保存曲线数据？"), _("确认"),wxYES_NO, this)==wxYES)
{
    wxFileDialog savdlgtu(this, _("保存球差曲线数据"), _(""), _(""), _("Excel 2003(*.csv)|*.csv"),  wxFD_SAVE, wxDefaultPosition);
    if(savdlgtu.ShowModal()!=wxID_OK) return;
    file.Clear();
    file=savdlgtu.GetPath();
    char filesavetu[100];/*存储打开的文件名*/
    strncpy(filesavetu, (const char*)file.mb_str(wxConvLocal), 99);
    FILE *savfileptu;
    savfileptu=fopen(filesavetu,"w");
    for(int i=1;i<=100;i++) fprintf(savfileptu,"%f,%f,%f\n",plot_sph_dFC[0][i].dl,plot_sph_dFC[1][i].dl,plot_sph_dFC[2][i].dl);
    fclose(savfileptu);
}
}

/*
void drawDlg::OnDrawDis( wxCommandEvent& event )
{


char wwwww[100];string qwqwqw="";





    / *畸变,dFC* /
    for(int ii=1;ii<=100;ii++){
        for(int jj=0;jj<3;jj++)
        {
            raytracing(0,ii/2.0*sys.w2/100.0000000000000,0,plot_ch[jj],'P');
            double y0temp=(temp[sys.N].lx-cal_l)*tan(temp[ii].ux);
            raytracing(0,ii*sys.w2/200,0,plot_ch[jj],'M');
            double yptemp=(temp[sys.N].lx-cal_l)*tan(temp[ii].ux);
            plot_dis_dFC[jj][ii].dy=(yptemp-y0temp)/y0temp;
        }



sprintf(wwwww,"%d %e\n",ii,plot_dis_dFC[0][ii].dy);
qwqwqw+=wwwww;

    }
    wxClientDC dc(this);

    dc.SetPen(penblack);
    dc.DrawText(_("畸变"),wxPoint(50 ,50));
    for(int i=1;i<=400;i++)
        for(int j=-1;j<=1;j++){
            dc.DrawPoint(wxPoint(200+j,i));
            dc.DrawPoint(wxPoint(i,400+j));
    }

    dc.SetPen(pend);
    for(int i=1;i<=100;i++)for(int x=-2;x<=2;x++)for(int y=-2;y<=2;y++)
        dc.DrawPoint(wxPoint((int)(plot_dis_dFC[0][i].dy/0.0005*10000+200+x),((101-i)*4)*100+y));
    dc.SetPen(penF);
    for(int i=1;i<=100;i++)for(int x=-2;x<=2;x++)for(int y=-2;y<=2;y++)
        dc.DrawPoint(wxPoint((int)(plot_dis_dFC[1][i].dy/0.0005+200+x),((101-i)*4)+y));
    dc.SetPen(penC);
    for(int i=1;i<=100;i++)for(int x=-2;x<=2;x++)for(int y=-2;y<=2;y++)
        dc.DrawPoint(wxPoint((int)(plot_dis_dFC[2][i].dy/0.0005+200+x),((101-i)*4)+y));

    dc.SetPen((wxNullPen));




wxString qqqqqqq(qwqwqw.c_str(), wxConvUTF8);
wxMessageBox(qqqqqqq, _("参数"));


}

	void drawDlg::OnSaveDis( wxCommandEvent& event ){}

		void drawDlg::OnDrawFld( wxCommandEvent& event ){}

		void drawDlg::OnSaveFld( wxCommandEvent& event ){}
*/

void raytracing(double in_l,double in_u,double in_h,char light_mode,char trace_mode)/*光线追踪计算*/
{
    int i;
    currentn(light_mode);

    for(i=1;i<=sys.N;i++)
    {
        if(i==1){temp[1].lw=in_l;temp[1].uw=in_u;temp[1].h=in_h;}                /* 第一个面读入物空间参数，赋值*/
        else    {temp[i].uw=temp[i-1].ux;temp[i].lw=temp[i-1].lx-temp[i-1].d;}   /* u=上一个u'，l=上一个l'-上一面到本面d*/

        if(trace_mode=='P')/*Paraxial近轴*/
        {
            if(temp[i].uw==0) temp[i].iw=temp[i].h/temp[i].r;                             /*u=0,平行入射，i=h/r*/
                    else      temp[i].iw=(temp[i].lw-temp[i].r)*temp[i].uw/temp[i].r;     /*i=(l-r)*u/r*/
            temp[i].ix=temp[i].iw*temp[i].nw/temp[i].nx;            /*   i'=i*n/n'  */
            temp[i].ux=temp[i].uw+temp[i].iw-temp[i].ix;            /*   u'=u+i-i'  */
            temp[i].lx=temp[i].ix*temp[i].r/temp[i].ux+temp[i].r;   /* l'=i'*r/u'+r */
            temp[i].h=temp[i].lw*temp[i].uw;                        /*    h=l*u     */
        }
        if(trace_mode=='M')/*Meridional子午*/
        {
            if(temp[i].uw==0) temp[i].iw=asin(temp[i].h/temp[i].r);                                /* 平行入射 sin I=h/r  */
                    else      temp[i].iw=asin((temp[i].lw-temp[i].r)*sin(temp[i].uw)/temp[i].r);   /* sin I=(l-r)*sin u/r */
            temp[i].ix=asin(sin(temp[i].iw)*temp[i].nw/temp[i].nx);          /*   sin i'=sin i*n/n'  */
            temp[i].ux=temp[i].uw+temp[i].iw-temp[i].ix;                     /*       U'=U+I-I'      */
            temp[i].lx=sin(temp[i].ix)*temp[i].r/sin(temp[i].ux)+temp[i].r;  /* L'=sin i'*r/sin u'+r */
            temp[i].h=temp[i].lw*sin(temp[i].uw);                            /*       h=L*sinU       */
            if(temp[i].uw==0)temp[i].PA=temp[i].h/cos((temp[i].iw-temp[i].uw)/2); /*PA=h/cos((I-U)/2)*/
                   else      temp[i].PA=temp[i].lw*sin(temp[i].uw)/cos((temp[i].iw-temp[i].uw)/2);/*PA=l*sinU/cos((I-U)/2)*/


        }
    }
}

void currentn(char cur_mode)/*根据cur_mode：'d','F','C'，设置当前nw和nx值  */
{
    int i;
    for(i=1;i<=sys.N;i++){temp[i].r=len[i].r;temp[i].d=len[i].d;}
    switch(cur_mode)
    {
        case 'd':for(i=1;i<=sys.N;i++){temp[i].nx=len[i].nd;temp[i].nw=len[i-1].nd;}break;
        case 'F':for(i=1;i<=sys.N;i++){temp[i].nx=len[i].nF;temp[i].nw=len[i-1].nF;}break;
        case 'C':for(i=1;i<=sys.N;i++){temp[i].nx=len[i].nC;temp[i].nw=len[i-1].nC;}break;
    }
}

void thinbeam(void)/*细光束像散场曲等计算*/
{
    int i;
    raytracing(0,-sys.w2/2,0,'d','M');/*子午面轴外点d光主光线各面数据，暂存于temp[1~N]*/
    for(i=1;i<=sys.N;i++)
        afc[i].x=temp[i].PA*temp[i].PA/(2*temp[i].r);/*x=PA^2/2r*/
    for(i=1;i<=sys.N;i++)
    {
        if(i==1){
            afc[i].tw=INF;
            afc[i].sw=INF;
            afc[i].D=0;
            }
           else {
            afc[i].D=(temp[i-1].h-temp[i].h)/sin(temp[i-1].ux);
            afc[i].tw=afc[i-1].tx-afc[i].D;
            afc[i].sw=afc[i-1].sx-afc[i].D;
            }
        double ys;/*杨氏公式右边表达式*/
        ys=(temp[i].nx*cos(temp[i].ix)-temp[i].nw*cos(temp[i].iw))/temp[i].r;
        afc[i].tx=(temp[i].nx*cos(temp[i].ix)*cos(temp[i].ix))/((temp[i].nw*cos(temp[i].iw)*cos(temp[i].iw))/afc[i].tw+ys);
        afc[i].sx=temp[i].nx/(temp[i].nw/afc[i].sw+ys);
    }
    cal_lt=afc[sys.N].tx*cos(temp[sys.N].ux)+afc[sys.N].x;
    cal_ls=afc[sys.N].sx*cos(temp[sys.N].ux)+afc[sys.N].x;
    cal_xt=cal_lt-cal_l;
    cal_xs=cal_ls-cal_l;
    cal_Dxts=cal_xt-cal_xs;
}
