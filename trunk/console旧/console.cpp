/***************************************************************
 * Name:      console.cpp
 * Purpose:   ����׷�ٳ��� �����а汾 ���012��qianwei
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

#define MAX (201)    /*��������200,0��Ϊ��ǰ��Ŀ���*/
#define INF (1e200)   /*����Զ*/

string filename="˫����͸��";

system sys;
surface len[MAX];/*1~NΪ�������ݣ�0��dFC����Ϊ1��Ϊ����*/
trace temp[MAX];/*temp[MAX]���ڴ�Ÿ��μ���Ľ��*/
astifieldcur afc[MAX];
normal putong[MAX];

/** ����������� **/
double cal_f,cal_l,cal_lp,cal_y0,cal_dlm,cal_xt,cal_xs,cal_Dxts,cal_Dy;
/*       f'   l'     lp'    y0'    ��lm'    xt'   xs'     ��xts'   ��y'  */

/** �������� **/
double cal_lt,cal_ls;

void load(void);/*�����ļ�*/
void raytracing(double ,double ,double ,char ,char );/*�������׷�٣�dFC�����ģʽ���� */
void thinbeam(void);/*ϸ������ɢ�����ȼ���*/
void currentn(char );/*����cur_mode��'d','F','C'�����õ�ǰ�﷽nw����nxֵ  */

int main()
{
    load();

    FILE *filep;
    filep=fopen("˫����͸�����.doc","w");
fprintf(filep,"\n/******************* ������Ҫ���9������ *******************/\n\n");

    trace para_1;/*��һ�����*/
    raytracing(INF,0,sys.a2/2,'d','P');para_1=temp[sys.N];/*d���һ����*/
    cal_f=(sys.a2/2)/para_1.ux;
    cal_l=para_1.lx;
    fprintf(filep,"���뽹��   f'=%3.8f\n��˹���   l'=%3.8f\n",cal_f,cal_l);

    trace para_2;/*�ڶ������*/
    raytracing(sys.lpw,-sys.w2/2,0,'d','P');para_2=temp[sys.N];/*d��ڶ�����*/
    cal_lp=para_2.lx;
    cal_y0=(cal_lp-cal_l)*tan(para_2.ux);
    fprintf(filep,"��ͫ��    lp'=%3.8f\n���      y0'= %3.8f\n",cal_lp,cal_y0);

    trace meri_zsdby;/*���������ϵ��Ե����*/
    raytracing(INF,0,sys.a2/2,'d','M');meri_zsdby=temp[sys.N];/*���������ϵ�d���Ե����*/
    cal_dlm=meri_zsdby.lx-cal_l;
    fprintf(filep,"��������Lm'=%3.8f\n",cal_dlm);

    thinbeam();/*ϸ������ɢ�����ȼ���*/
    fprintf(filep,"���糡��  xt'=%3.8f\n",cal_xt);
    fprintf(filep,"��ʸ����  xs'=%3.8f\n",cal_xs);
    fprintf(filep,"��ɢ   ��xts'=%3.8f\n",cal_Dxts);

    trace meri_zwdz;/*�����������������*/
    raytracing(0,-sys.w2/2,0,'d','M');meri_zwdz=temp[sys.N];/*�����������d��������*/
    double zwdlp=meri_zwdz.lx,zwdup=meri_zwdz.ux,zwdyp=(zwdlp-cal_l)*tan(zwdup);
    cal_Dy=(zwdyp-cal_y0)/cal_y0;
    fprintf(filep,"��Ի��� ��y'=%3.8f\n",cal_Dy);

fprintf(filep,"\n/*******************      ��������       *******************/\n\n");

    raytracing(INF,0,0.707*sys.a2/2,'d','M');/*���������ϵ�d��0.707����*/
    fprintf(filep,"0.707�������ʣ������Lmax'=%3.8f\n",temp[sys.N].lx-cal_l);

    fprintf(filep,"��������Tm'=%3.8f\n",cal_dlm*tan(meri_zsdby.ux));
    fprintf(filep,"���Ի��� ��y'=%3.8f\n",zwdyp-cal_y0);
    fprintf(filep,"ʵ�����  yp'= %3.8f\n",zwdyp);

    trace meri_zwds;/*������������Ϲ���*/
    raytracing(sys.a2/2/tan(-sys.w2/2),-sys.w2/2,sys.a2/2,'d','M');meri_zwds=temp[sys.N];/*�����������d���Ϲ���*/
    double zwdla=meri_zwds.lx,zwdua=meri_zwds.ux,zwdya=(zwdla-cal_l)*tan(zwdua);
    trace meri_zwdx;/*������������¹���*/
    raytracing(-sys.a2/2/tan(-sys.w2/2),-sys.w2/2,-sys.a2/2,'d','M');meri_zwdx=temp[sys.N];/*�����������d���¹���*/
    double zwdlb=meri_zwdx.lx,zwdub=meri_zwdx.ux,zwdyb=(zwdlb-cal_l)*tan(zwdub);
    double cal_Kt=(zwdya+zwdyb)/2-zwdyp;
    fprintf(filep,"�������  Kt'= %3.8f\n",cal_Kt);

    trace meri_zwdzF;/*�����������F��������*/
    raytracing(0,-sys.w2/2,0,'F','M');meri_zwdzF=temp[sys.N];/*�����������F��������*/
    double zwdlF=meri_zwdzF.lx,zwduF=meri_zwdzF.ux,zwdyF=(zwdlF-cal_l)*tan(zwduF);
    trace meri_zwdzC;/*�����������C��������*/
    raytracing(0,-sys.w2/2,0,'C','M');meri_zwdzC=temp[sys.N];/*�����������C��������*/
    double zwdlC=meri_zwdzC.lx,zwduC=meri_zwdzC.ux,zwdyC=(zwdlC-cal_l)*tan(zwduC);
    fprintf(filep,"d��ʵ�����y'= %3.8f\n",zwdyp);
    fprintf(filep,"F��ʵ�����y'= %3.8f\n",zwdyF);
    fprintf(filep,"C��ʵ�����y'= %3.8f\n",zwdyC);
    fprintf(filep,"����ɫ���ych'=%3.8f\n",zwdyF-zwdyC);
    fprintf(filep,"λ��ɫ���lch'=%3.8f\n",zwdlF-zwdlC);

    double cal_F=(sys.a2/2)/sin(meri_zsdby.ux);
    double cal_df=cal_F-cal_f;
    double cal_OSC=cal_df/cal_f-cal_dlm/(cal_l-cal_lp);/*�������Ҳ�*/
    fprintf(filep,"�������Ҳ�OSC= %3.8f\n",cal_OSC);
    double cal_Ks=cal_y0*cal_OSC;
    fprintf(filep,"��ʸ���  Ks'= %3.8f\n",cal_Ks);

    fprintf(filep,"d������ȫ�׾����%3.8f\n",meri_zsdby.lx-para_1.lx);

fprintf(filep,"\n/*******************     ������ͨ����    *******************/\n\n");

    for(int i=1;i<=sys.yanglishu;i++)
    {
        raytracing(putong[i].L,putong[i].Uh,putong[i].H,'d','M');
        putong[i].Lx=temp[i].lx;putong[i].Uhx=temp[i].ux;putong[i].Ujx=putong[i].Uhx/3.141592654*180;
        fprintf(filep,"���룺L=%.4e U=%.4f H=%.4e \n                    �����L'=%.4e U'=%.4e\n\n",putong[i].L,putong[i].Uj,putong[i].H,putong[i].Lx,putong[i].Ujx);
    }
fclose(filep);

/*******************         ��ͼ        *******************/

/*���,dFC*/
    FILE *sph;
    sph=fopen("˫����͸�����.csv","w");
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

/*��������*/
    /** �� **/

/*
/ *����ɫ��* /
trace beid,beiC,beiF,qiud;
trace beid1,beiF1,beiC1;/ *��һ�����* /
raytracing(INF,0,sys.a2/2,'d','P');beid1=temp[sys.N];
raytracing(INF,0,sys.a2/2,'C','P');beiC1=temp[sys.N];
raytracing(INF,0,sys.a2/2,'F','P');beiF1=temp[sys.N];
raytracing(sys.lpw,-sys.w2/2,0,'d','P');beid=temp[sys.N];
raytracing(sys.lpw,-sys.w2/2,0,'F','P');beiF=temp[sys.N];
raytracing(sys.lpw,-sys.w2/2,0,'C','P');beiC=temp[sys.N];

printf("\n\n\n%3.8f\n%3.8f\n%3.8f\n\n",(beiC.lx-beiC1.lx)*beiC.ux,(beiF.lx-beiF1.lx)*beiF.ux,(beid.lx-beid1.lx)*beid.ux);
*/
    //printf("\n\n���س����˳�����");getchar();
    return 0;
}


void load(void)/*�����ļ�*/
{
    int i;
    FILE *fp;
    fp=fopen("˫����͸��.dat","r");
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
    len[0].r=len[0].d=len[0].nd=len[0].nF=len[0].nC=1;/*��ǰ��Ŀ���,������,ֱ�Ӹ�ֵ{1,1,1,1,1}����ʾ-std=c++0x����*/
}

void raytracing(double in_l,double in_u,double in_h,char light_mode,char trace_mode)/*����׷�ټ���*/
{
    int i;
    currentn(light_mode);

    for(i=1;i<=sys.N;i++)
    {
        if(i==1){temp[1].lw=in_l;temp[1].uw=in_u;temp[1].h=in_h;}                /* ��һ���������ռ��������ֵ*/
        else    {temp[i].uw=temp[i-1].ux;temp[i].lw=temp[i-1].lx-temp[i-1].d;}   /* u=��һ��u'��l=��һ��l'-��һ�浽����d*/

        if(trace_mode=='P')/*Paraxial����*/
        {
            if(temp[i].uw==0) temp[i].iw=temp[i].h/temp[i].r;                             /*u=0,ƽ�����䣬i=h/r*/
                    else      temp[i].iw=(temp[i].lw-temp[i].r)*temp[i].uw/temp[i].r;     /*i=(l-r)*u/r*/
            temp[i].ix=temp[i].iw*temp[i].nw/temp[i].nx;            /*   i'=i*n/n'  */
            temp[i].ux=temp[i].uw+temp[i].iw-temp[i].ix;            /*   u'=u+i-i'  */
            temp[i].lx=temp[i].ix*temp[i].r/temp[i].ux+temp[i].r;   /* l'=i'*r/u'+r */
            temp[i].h=temp[i].lw*temp[i].uw;                        /*    h=l*u     */
        }
        if(trace_mode=='M')/*Meridional����*/
        {
            if(temp[i].uw==0) temp[i].iw=asin(temp[i].h/temp[i].r);                                /* ƽ������ sin I=h/r  */
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

void currentn(char cur_mode)/*����cur_mode��'d','F','C'�����õ�ǰnw��nxֵ  */
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

void thinbeam(void)/*ϸ������ɢ�����ȼ���*/
{
    int i;
    raytracing(0,-sys.w2/2,0,'d','M');/*�����������d�������߸������ݣ��ݴ���temp[1~N]*/
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
        double ys;/*���Ϲ�ʽ�ұ߱��ʽ*/
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
