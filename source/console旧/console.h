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

struct system/*ϵͳ�������*/
{
    int N;/*�������*/
    double a2; /*����ֱ��2a*/
    double w2j;/*�ӳ���С2W���Ƕ�*/
    double w2; /*�ӳ���С2W������*/
    double lpw;/*��ͫ��,�﷽lp*/
    int yanglishu;/*��ͨ���߼��㣬L,U,H�����ں��棬��yanglishu��*/
};

struct surface/*�����������*/
{
    double r;/*���ʰ뾶*/
    double d;/*����һ��ľ���*/
    double nd;/*d��������*/
    double nF;/*F��������*/
    double nC;/*C��������*/
};

struct trace/*���ߴ��ݵ�ĳ����Ĳ���*/
{
    double r; /*��ǰ���������ʰ뾶*/
    double d; /*��ǰ�����浽��һ������ľ���*/
    double nw;/*��ǰ��ռ�������*/
    double nx;/*��ǰ��ռ�������*/
    double lw;
    double lx;
    double uw;
    double ux;
    double h;
    double iw;/*��ǰ��ռ������*/
    double ix;/*��ǰ��ռ�����*/
    double PA;
};

struct astifieldcur/*��ɢ����Astigmatism Field curvature*/
{
    double x;/*ʸ��*//*http://jpkc.zju.edu.cn/k/548/CADweb/pages/chp11.htm#������������ߵ�ϸ�������λ�õļ���*/
    double D;/*��������������ߵľ���*/
    double tw;
    double tx;
    double sw;
    double sx;
};

struct normal/*������ͨ���߼���*/
{
    int check;
    double L,Uj,Uh,H;/* Uj�Ƕȣ�U���ȡ�U�������룬LH��������һ����check==110����ʾ����LU��check==011����ʾ����UH */
    double Lx,Ujx,Uhx;/*�������ӳ��ǣ��Ƕȡ�*/
};

struct plot/*�洢��������*/
{
    double l,u,dl;
};
