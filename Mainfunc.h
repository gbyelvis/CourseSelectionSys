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

typedef struct   //定义账户和密码的结构体
{
    string aco;
    string pas;
}A;

typedef struct      //定义课程的结构体
{
    string KC_numb;
    string C_name;
    string C_Teacher_name;
    string C_score;
    string C_room;
    string C_time;
}cour;

void Sec_Main();    //第二程序入口，解决了回调程序

void Main_display();   //打印登入页面

void read_acount(ifstream &,ifstream &,vector<A>&,vector<cour>&);    //读取账户、密码和课程信息

void ini_acount_cour(ifstream &,vector<cour>&,double&);     //读取用户信息

void Sys_display();      //打印标题、题头

void gotoxy(int,int);     //设定光标位置

void error_Prompt(string);       //错误信息提示

void pass_disply(string);          //打印修改密码界面

void tem_cour_disp(map<string,cour>);   //打印临时课程信息

void save_cour(map<string,cour>,string);    //保存课程

void Storage_pass(map<string,string>);  //密码修改保存


#endif // MAINFUNC_H_INCLUDED
