#ifndef STUCLASS_H_INCLUDED
#define STUCLASS_H_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream>
#include <ostream>
#include <vector>
#include <string>
#include <map>
#include "Mainfunc.h"

using namespace std;

class StudImpl;  //预声明

class StuPassw   //用户密码类
{
public:
    StuPassw()=default;
    StuPassw(string,vector<A>);
    string Getacount();    //读取账户名称
    bool Reflect(StudImpl&) const;    //验证账户和密码
    void Pass_modify(StudImpl&);      //修改密码
    ~StuPassw(){}
private:
    string Acount;              //存取用户帐户
    map<string,string> wm;            //存取密码
};

class Course    //课程信息类
{
public:
    Course()=default;
    Course(vector<cour>);
    void _tem(map<string,cour>&);    //存取用户信息
    void disp(StudImpl&);         //打印课程信息
    void Mod(StudImpl&,double&);   //删除课程信息
    void _sech(StudImpl&,double&);  //添加课程信息
    ~Course(){}
private:
    map<string,cour> _course;
};

class StudImpl:public StuPassw,public Course      //学生信息类
{
public:
    StudImpl(string ac,vector<A> Aa,vector<cour> Cc,vector<cour> tab,double _sum):StuPassw(ac,Aa),Course(Cc),table(tab),sum(_sum){}
    void C_main(StudImpl&);         //第一级子菜单
    void X_main(StudImpl&);         //第二级子菜单
    void tem(map<string,cour>&);    //存取课程信息
    void display(StudImpl&);        //打印用户全信息
    void Modify(StudImpl&);         //删除用户课程信息
    void _search(StudImpl&);        //添加课程信息
    bool validation_sum(StudImpl&);   //验证学分
    double Getsum();                //读取学分
    ~StudImpl(){}
private:
    Course table;      //用户课程信息
    double sum;        //用户学分
};


#endif // STUCLASS_H_INCLUDED
