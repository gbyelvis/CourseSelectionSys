#ifndef MAINFUNC_H_INCLUDED
#define MAINFUNC_H_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream>
#include <ostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

typedef struct   //�����˻�������Ľṹ��
{
    string aco;
    string pas;
}A;

typedef struct      //����γ̵Ľṹ��
{
    string KC_numb;
    string C_name;
    string C_Teacher_name;
    string C_score;
    string C_room;
    string C_time;
}cour;

void Sec_Main();    //�ڶ�������ڣ�����˻ص�����

void Main_display();   //��ӡ����ҳ��

void read_acount(ifstream &,ifstream &,vector<A>&,vector<cour>&);    //��ȡ�˻�������Ϳγ���Ϣ

void ini_acount_cour(ifstream &,vector<cour>&,double&);     //��ȡ�û���Ϣ

void Sys_display();      //��ӡ���⡢��ͷ

void gotoxy(int,int);     //�趨���λ��

void error_Prompt(string);       //������Ϣ��ʾ

void pass_disply(string);          //��ӡ�޸��������

void tem_cour_disp(map<string,cour>);   //��ӡ��ʱ�γ���Ϣ

void save_cour(map<string,cour>,string);    //����γ�

void Storage_pass(map<string,string>);  //�����޸ı���


#endif // MAINFUNC_H_INCLUDED
