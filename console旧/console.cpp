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

#include <iostream>
#include <string>
#include <stdio.h>
#include <cmath>
#include "console.h"
using namespace std;

#define MAX (201)    /*最多表面数200,0号为最前面的空气*/
#define INF (1e200)   /*无穷远*/

string filename="双胶合透镜";

system sys;
surface len[MAX];/*1~N为输入数据，0号dFC设置为1，为空气*/
trace temp[MAX];/*temp[MAX]用于存放各次计算的结果*/
astifieldcur afc[MAX];
normal putong[MAX];

/** 基本待求参数 **/
double cal_f,cal_l,cal_lp,cal_y0,cal_dlm,cal_xt,cal_xs,cal_Dxts,cal_Dy;
/*       f'   l'     lp'    y0'    δlm'    xt'   xs'     Δxts'   Δy'  */

/** 其他变量 **/
double cal_lt,cal_ls;

void load(void);/*加载文件*/
void raytracing(double ,double ,double ,char ,char );/*计算光线追踪，dFC各光各模式计算 */
void thinbeam(void);/*细光束像散场曲等计算*/
void currentn(char );/*根据cur_mode：'d','F','C'，设置当前物方nw和像方nx值  */

int main()
{
    load();

    FILE *filep;
    filep=fopen("双胶合透镜输出.doc","w");
fprintf(filep,"\n/******************* 任务书要求的9个数据 *******************/\n\n");

    trace para_1;/*第一近轴光*/
    raytracing(INF,0,sys.a2/2,'d','P');para_1=temp[sys.N];/*d光第一近轴*/
    cal_f=(sys.a2/2)/para_1.ux;
    cal_l=para_1.lx;
    fprintf(filep,"理想焦距   f'=%3.8f\n高斯像距   l'=%3.8f\n",cal_f,cal_l);

    trace para_2;/*第二近轴光*/
    raytracing(sys.lpw,-sys.w2/2,0,'d','P');para_2=temp[sys.N];/*d光第二近轴*/
    cal_lp=para_2.lx;
    cal_y0=(cal_lp-cal_l)*tan(para_2.ux);
    fprintf(filep,"出瞳距    lp'=%3.8f\n像高      y0'= %3.8f\n",cal_lp,cal_y0);

    trace meri_zsdby;/*子午面轴上点边缘光线*/
    raytracing(INF,0,sys.a2/2,'d','M');meri_zsdby=temp[sys.N];/*子午面轴上点d光边缘光线*/
    cal_dlm=meri_zsdby.lx-cal_l;
    fprintf(filep,"轴向球差δLm'=%3.8f\n",cal_dlm);

    thinbeam();/*细光束像散场曲等计算*/
    fprintf(filep,"子午场曲  xt'=%3.8f\n",cal_xt);
    fprintf(filep,"弧矢场曲  xs'=%3.8f\n",cal_xs);
    fprintf(filep,"像散   Δxts'=%3.8f\n",cal_Dxts);

    trace meri_zwdz;/*子午面轴外点主光线*/
    raytracing(0,-sys.w2/2,0,'d','M');meri_zwdz=temp[sys.N];/*子午面轴外点d光主光线*/
    double zwdlp=meri_zwdz.lx,zwdup=meri_zwdz.ux,zwdyp=(zwdlp-cal_l)*tan(zwdup);
    cal_Dy=(zwdyp-cal_y0)/cal_y0;
    fprintf(filep,"相对畸变 Δy'=%3.8f\n",cal_Dy);

fprintf(filep,"\n/*******************      其它参数       *******************/\n\n");

    raytracing(INF,0,0.707*sys.a2/2,'d','M');/*子午面轴上点d光0.707带光*/
    fprintf(filep,"0.707带光最大剩余球差δLmax'=%3.8f\n",temp[sys.N].lx-cal_l);

    fprintf(filep,"垂轴球差δTm'=%3.8f\n",cal_dlm*tan(meri_zsdby.ux));
    fprintf(filep,"线性畸变 δy'=%3.8f\n",zwdyp-cal_y0);
    fprintf(filep,"实际像高  yp'= %3.8f\n",zwdyp);

    trace meri_zwds;/*子午面轴外点上光线*/
    raytracing(sys.a2/2/tan(-sys.w2/2),-sys.w2/2,sys.a2/2,'d','M');meri_zwds=temp[sys.N];/*子午面轴外点d光上光线*/
    double zwdla=meri_zwds.lx,zwdua=meri_zwds.ux,zwdya=(zwdla-cal_l)*tan(zwdua);
    trace meri_zwdx;/*子午面轴外点下光线*/
    raytracing(-sys.a2/2/tan(-sys.w2/2),-sys.w2/2,-sys.a2/2,'d','M');meri_zwdx=temp[sys.N];/*子午面轴外点d光下光线*/
    double zwdlb=meri_zwdx.lx,zwdub=meri_zwdx.ux,zwdyb=(zwdlb-cal_l)*tan(zwdub);
    double cal_Kt=(zwdya+zwdyb)/2-zwdyp;
    fprintf(filep,"子午彗差  Kt'= %3.8f\n",cal_Kt);

    trace meri_zwdzF;/*子午面轴外点F光主光线*/
    raytracing(0,-sys.w2/2,0,'F','M');meri_zwdzF=temp[sys.N];/*子午面轴外点F光主光线*/
    double zwdlF=meri_zwdzF.lx,zwduF=meri_zwdzF.ux,zwdyF=(zwdlF-cal_l)*tan(zwduF);
    trace meri_zwdzC;/*子午面轴外点C光主光线*/
    raytracing(0,-sys.w2/2,0,'C','M');meri_zwdzC=temp[sys.N];/*子午面轴外点C光主光线*/
    double zwdlC=meri_zwdzC.lx,zwduC=meri_zwdzC.ux,zwdyC=(zwdlC-cal_l)*tan(zwduC);
    fprintf(filep,"d光实际像高y'= %3.8f\n",zwdyp);
    fprintf(filep,"F光实际像高y'= %3.8f\n",zwdyF);
    fprintf(filep,"C光实际像高y'= %3.8f\n",zwdyC);
    fprintf(filep,"倍率色差δych'=%3.8f\n",zwdyF-zwdyC);
    fprintf(filep,"位置色差δlch'=%3.8f\n",zwdlF-zwdlC);

    double cal_F=(sys.a2/2)/sin(meri_zsdby.ux);
    double cal_df=cal_F-cal_f;
    double cal_OSC=cal_df/cal_f-cal_dlm/(cal_l-cal_lp);/*初级正弦差*/
    fprintf(filep,"初级正弦差OSC= %3.8f\n",cal_OSC);
    double cal_Ks=cal_y0*cal_OSC;
    fprintf(filep,"弧矢彗差  Ks'= %3.8f\n",cal_Ks);

    fprintf(filep,"d光轴上全孔径球差%3.8f\n",meri_zsdby.lx-para_1.lx);

fprintf(filep,"\n/*******************     任意普通光线    *******************/\n\n");

    for(int i=1;i<=sys.yanglishu;i++)
    {
        raytracing(putong[i].L,putong[i].Uh,putong[i].H,'d','M');
        putong[i].Lx=temp[i].lx;putong[i].Uhx=temp[i].ux;putong[i].Ujx=putong[i].Uhx/3.141592654*180;
        fprintf(filep,"输入：L=%.4e U=%.4f H=%.4e \n                    输出：L'=%.4e U'=%.4e\n\n",putong[i].L,putong[i].Uj,putong[i].H,putong[i].Lx,putong[i].Ujx);
    }
fclose(filep);

/*******************         画图        *******************/

/*球差,dFC*/
    FILE *sph;
    sph=fopen("双胶合透镜球差.csv","w");
    plot plot_sph_dFC[3][101];
    char plot_ch[3]={'d','F','C'};
    for(int i=1;i<=100;i++)
    {
        for(int j=0;j<3;j++)
        {
            raytracing(INF,0,i/100.0*sys.a2/2,plot_ch[j],'M');
            plot_sph_dFC[j][i].l=temp[sys.N].lx;
            plot_sph_dFC[j][i].dl=plot_sph_dFC[j][i].l-cal_l;
        }
        fprintf(sph,"%f,%f,%f\n",plot_sph_dFC[0][i].dl,plot_sph_dFC[1][i].dl,plot_sph_dFC[2][i].dl);
    }
    fclose(sph);

/*场曲畸变*/
    /** 空 **/

/*
/ *倍率色差* /
trace beid,beiC,beiF,qiud;
trace beid1,beiF1,beiC1;/ *第一近轴光* /
raytracing(INF,0,sys.a2/2,'d','P');beid1=temp[sys.N];
raytracing(INF,0,sys.a2/2,'C','P');beiC1=temp[sys.N];
raytracing(INF,0,sys.a2/2,'F','P');beiF1=temp[sys.N];
raytracing(sys.lpw,-sys.w2/2,0,'d','P');beid=temp[sys.N];
raytracing(sys.lpw,-sys.w2/2,0,'F','P');beiF=temp[sys.N];
raytracing(sys.lpw,-sys.w2/2,0,'C','P');beiC=temp[sys.N];

printf("\n\n\n%3.8f\n%3.8f\n%3.8f\n\n",(beiC.lx-beiC1.lx)*beiC.ux,(beiF.lx-beiF1.lx)*beiF.ux,(beid.lx-beid1.lx)*beid.ux);
*/
    //printf("\n\n按回车键退出程序");getchar();
    return 0;
}


void load(void)/*加载文件*/
{
    int i;
    FILE *fp;
    fp=fopen("双胶合透镜.dat","r");
    fscanf(fp,"%d,%le,%le,%le,%d\n\n",&sys.N,&sys.lpw,&sys.a2,&sys.w2j,&sys.yanglishu);
    sys.w2=sys.w2j/180.0*3.141592654;
    for(i=1;i<=sys.N;i++) fscanf(fp,"%le,%le,%le,%le,%le\n",&len[i].r,&len[i].d,&len[i].nd,&len[i].nF,&len[i].nC);
    fscanf(fp,"\n");
    for(i=1;i<=sys.yanglishu;i++)
    {
     /*   fscanf(fp,"%d,",&putong[i].check);
        if(putong[i].check==110) {
                        fscanf(fp,"%le,%le\n",&putong[i].L,&putong[i].Uj);
                        putong[i].Uh=putong[i].Uj/180*3.141592654;
                        putong[i].H=putong[i].L*tan(putong[i].Uh);
                        }
        else if(putong[i].check==011) {
                        fscanf(fp,"%le,%le\n",&putong[i].Uj,&putong[i].H);
                        putong[i].Uh=putong[i].Uj/180*3.141592654;
                        putong[i].L=putong[i].H/tan(putong[i].Uh);}
                        */
        fscanf(fp,"%le,%le,%le\n",&putong[i].L,&putong[i].Uj,&putong[i].H);
    }
    fclose(fp);
    len[0].r=len[0].d=len[0].nd=len[0].nF=len[0].nC=1;/*最前面的空气,或物面,直接赋值{1,1,1,1,1}会提示-std=c++0x限制*/
}

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
