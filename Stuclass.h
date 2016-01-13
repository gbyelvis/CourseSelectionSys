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

class StudImpl;  //Ԥ����

class StuPassw   //�û�������
{
public:
    StuPassw()=default;
    StuPassw(string,vector<A>);
    string Getacount();    //��ȡ�˻�����
    bool Reflect(StudImpl&) const;    //��֤�˻�������
    void Pass_modify(StudImpl&);      //�޸�����
    ~StuPassw(){}
private:
    string Acount;              //��ȡ�û��ʻ�
    map<string,string> wm;            //��ȡ����
};

class Course    //�γ���Ϣ��
{
public:
    Course()=default;
    Course(vector<cour>);
    void _tem(map<string,cour>&);    //��ȡ�û���Ϣ
    void disp(StudImpl&);         //��ӡ�γ���Ϣ
    void Mod(StudImpl&,double&);   //ɾ���γ���Ϣ
    void _sech(StudImpl&,double&);  //��ӿγ���Ϣ
    ~Course(){}
private:
    map<string,cour> _course;
};

class StudImpl:public StuPassw,public Course      //ѧ����Ϣ��
{
public:
    StudImpl(string ac,vector<A> Aa,vector<cour> Cc,vector<cour> tab,double _sum):StuPassw(ac,Aa),Course(Cc),table(tab),sum(_sum){}
    void C_main(StudImpl&);         //��һ���Ӳ˵�
    void X_main(StudImpl&);         //�ڶ����Ӳ˵�
    void tem(map<string,cour>&);    //��ȡ�γ���Ϣ
    void display(StudImpl&);        //��ӡ�û�ȫ��Ϣ
    void Modify(StudImpl&);         //ɾ���û��γ���Ϣ
    void _search(StudImpl&);        //��ӿγ���Ϣ
    bool validation_sum(StudImpl&);   //��֤ѧ��
    double Getsum();                //��ȡѧ��
    ~StudImpl(){}
private:
    Course table;      //�û��γ���Ϣ
    double sum;        //�û�ѧ��
};


#endif // STUCLASS_H_INCLUDED
