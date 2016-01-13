#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <ostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <map>
#include <memory>
#include <iomanip>
#include <conio.h>
#include "Stuclass.h"
#include "Mainfunc.h"

using namespace std;

static int c = 0;

map<string,cour> temporary;   //��ȡ��Ϣ��ʱ����

const string s = "  ********************************************************";

StuPassw::StuPassw(string ac,vector<A> Aa):Acount(ac)       //��ʼ���û�������
{
    for(auto r : Aa)
    {
        wm.insert(make_pair(r.aco,r.pas));       //����Ԫ��
    }
}

bool StuPassw::Reflect(StudImpl& q) const     //��֤�û��˻���������
{
    string ac = "";
    if(c)          //�˻�����������������
    {
        gotoxy(25,19);
        cin>>ac;
    }
    string pass;
    gotoxy(25,20);
    cin>>pass;
    auto map_it = wm.find(Acount);              //find�����ҵ����û���Ϣ
    if(map_it != wm.cend() && pass == map_it->second)    //������֤
    {
        system("cls");
        return true;
    }
    else          //������֤
    {
        error_Prompt("�˺ź�����");
        Main_display();
        c = 1;
        q.Reflect(q);
    }
    return true;
}

void StuPassw::Pass_modify(StudImpl& q)        //�����޸ĺ���
{
    N:pass_disply(Acount);
    auto map_pass = wm.find(Acount);      //find�����ҵ����û���Ϣ
    string s3,_s3,_s3_;
    cout<<'\t'<<s<<endl
        <<'\t'<<"  **      Acount:"<<Acount<<'\t'<<'\t'<<'\t'<<'\t'<<"**"<<endl
        <<'\t'<<"  **Old Password:"<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"**"<<endl
        <<'\t'<<"  **New Password:"<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"**"<<endl
        <<'\t'<<"  **Againt New_P:"<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"**"<<endl
        <<'\t'<<s<<endl;
    gotoxy(25,4);
    cin>>s3;
    gotoxy(25,5);
    cin>>_s3;
    gotoxy(25,6);
    cin>>_s3_;
    if(map_pass->second != s3)    //��֤ԭ����
    {
        error_Prompt("ԭ����");    //������Ϣ��ʾ
        goto N;
    }
    else if(_s3 != _s3_)     //��֤���������������Ƿ���ȷ
    {
        error_Prompt("������");
        goto N;
    }
    else
    {
        map_pass->second = _s3;           //�޸��û�����
        Storage_pass(wm);                 //����ϵͳ�����ļ�
        system("cls");
        gotoxy(3,12);
        cout<<"==>�޸ĳɹ����밴���������_ _ _";
        getch();
        system("cls");
        q.C_main(q);        //����һ���Ӳ˵�
    }
}

string StuPassw::Getacount()      //��ȡ�û��˻�
{
    return Acount;
}

void Course::disp(StudImpl& q)     //�γ���Ϣ����
{
    system("cls");
    Sys_display();
    cout<<setw(9)<<'-'<<"----------------------------------------------------"<<endl;
    cout<<setw(9)<<'|'<<setw(11)<<"�γ̺�"<<'|'<<setw(11)<<"�γ�"<<'|'<<setw(6)<<"��ʦ"<<'|'<<setw(4)<<"ѧ��"<<'|'<<setw(10)<<"�ص�"<<'|'<<setw(4)<<"ʱ��"<<'|'<<endl;
    cout<<setw(9)<<'='<<"===================================================="<<endl;
    auto it = _course.cbegin();
    for(;it != _course.cend();it++)
    {
        cout<<setw(9)<<'|'<<setw(11)<<it->second.KC_numb<<'|'<<setw(11)<<it->second.C_name<<'|'<<setw(6)<<it->second.C_Teacher_name<<'|'<<setw(4)<<it->second.C_score<<'|'<<setw(10)<<it->second.C_room<<'|'<<setw(4)<<it->second.C_time<<'|'<<endl
            <<setw(9)<<'-'<<"----------------------------------------------------"<<endl;
    }
    cout<<"==>�������������һ��_";
    getch();
}

void Course::_sech(StudImpl& q,double& sum)    //���ѧ���γ���Ϣ
{
    Sys_display();         //��ӡҳ����ͷ
    cout<<endl<<"ע�⣺����\��#\��Ϊ�˳�\��ѡ��γ�\��,����\��@\��Ϊ��ʾ\���γ���Ϣ\��"<<endl
        <<'\t'<<"����ֻ��ʾ�γ�һ�Σ��Է�ֹ֮ǰѡ���Ŀγ�δ�����棩"<<endl<<endl
        <<'\t'<<"������γ̺�_��";
    q.tem(temporary);          //��ԭ�ȵĿγ̴洢��temporary
    string a1;
    cin>>a1;
    while(a1 != "#")
    {
        if(a1 != "@")
        {
            auto itt = _course.find(a1);
            if(itt != _course.cend())
            {
                int g = 1;
                for(auto ita = temporary.begin();ita != temporary.end();ita++)
                    if(ita->second.C_time == itt->second.C_time || ita->second.KC_numb == itt->second.KC_numb)  //��֤ʱ���Ƿ�ͬ���γ̺�
                    {
                        g = 0;
                        cout<<"���ظ�ѡ�Σ����߿γ�ʱ���г�ͻ"<<endl
                            <<'\t'<<"������γ̺�_��";
                        break;
                    }
                if(g)
                {   temporary.insert(make_pair(a1,itt->second));    //��ӵ����γ���Ϣ
                    string sss = itt->second.C_score;           //�ۼ�ѧ��
                    const char* o = sss.c_str();
                    sum += atof(o);
                    cout<<"����ɹ���"<<endl
                        <<'\t'<<"������γ̺�_��";
                }
            }
            else
                {cout<<"����ʧ�ܣ�"<<endl<<'\t'<<"������γ̺�_��";}
        }
        else
        {q.disp(q);q._sech(q,sum);}
        cin>>a1;
    }
    q.tem(temporary);          //��ԭ�ȵĿγ̴洢��temporary
    tem_cour_disp(temporary);   //��ʾ�γ���Ϣ
    char c;
    cout<<endl
    <<"==>���水\'Y\',ȡ����\'N\'��";
    cin>>c;
    while(true)
    {
        if(c == 'Y' || c == 'y')
        {
            save_cour(temporary,q.Getacount());     //����ѧ���γ���Ϣ
            cout<<"����ɹ�"<<endl
                <<endl<<"==>�������������һ��_";
            break;
        }
        else if(c == 'N' || c =='n')
        {
            cout<<"δ����"
                <<endl<<"==>�������������һ��_";
            break;
        }
        cin>>c;
    }
    getch();
    q.X_main(q);      //���صڶ����Ӳ˵�
}

void Course::_tem(map<string,cour> &tem)              //�γ���Ϣ��ʱ����
{
    for(auto it_ = _course.cbegin();it_ != _course.cend();it_++)
        tem.insert(make_pair(it_->first,it_->second));
    for(auto _it_ = tem.cbegin();_it_ != tem.cend();_it_++)
        _course.insert(make_pair(_it_->first,_it_->second));

}

void Course::Mod(StudImpl& q,double& sum)   //ɾ���γ�
{
    Sys_display();
    cout<<endl<<"ע�⣺����\��#\��Ϊ�˳�\��ɾ���γ�\��,����\��@\��Ϊ��ʾ\���γ���Ϣ\��"<<endl
        <<'\t'<<"����ֻ��ʾ�γ�һ�Σ��Է�ֹ֮ǰɾ�����Ŀγ�δ�����棩"<<endl<<endl
        <<'\t'<<"������γ̺�_��";
    string a1;
    cin>>a1;
    while(a1 != "#")
    {
        if(a1 != "@")
        {
            auto itt = _course.find(a1);
            if(itt != _course.cend())
            {
                _course.erase(itt);               //ɾ�������γ���Ϣ
                string sss = itt->second.C_score;     //�ۼ�ѧ��
                const char* o = sss.c_str();
                sum -= atof(o);
                cout<<"ɾ���ɹ���"<<endl
                    <<'\t'<<"������γ̺�_��";
            }
            else
                {cout<<"ɾ��ʧ�ܣ�"<<endl<<'\t'<<"������γ̺�_��";}
        }
        else
        {q.disp(q);q._sech(q,sum);}
        cin>>a1;
    }
    temporary.clear();      //�����ʱ����
    temporary = _course;    //��������
    tem_cour_disp(temporary);   //��ʾ�γ���Ϣ
    //q.tem(temporary);
    char c;
    cout<<endl
    <<"==>���水\'Y\',ȡ����\'N\'��";
    cin>>c;
    while(true)
    {
        if(c == 'Y' || c == 'y')
        {
            save_cour(temporary,q.Getacount());   //����ѧ���γ���Ϣ
            cout<<"����ɹ�"<<endl
                <<endl<<"==>�������������һ��_";
            break;
        }
        else if(c == 'N' || c =='n')
        {
            cout<<"δ����"
                <<endl<<"==>�������������һ��_";
            break;
        }
        cin>>c;
    }
    getch();
    q.X_main(q);     //���صڶ����Ӳ˵�
}

Course::Course(vector<cour> cou)      //��ʼ���γ���Ϣ��
{
    cour cs;
    for(auto r : cou)
    {
        cs.KC_numb = r.KC_numb;
        cs.C_name = r.C_name;
        cs.C_Teacher_name = r.C_Teacher_name;
        cs.C_score = r.C_score;
        cs.C_room = r.C_room;
        cs.C_time = r.C_time;
        _course.insert(make_pair(r.KC_numb,cs));
    }
}

void StudImpl::C_main(StudImpl& q)   //һ���Ӳ˵�
{
    Sys_display();
    cout<<"��ӭ��������ѡ�Σ�"<<endl<<endl
        <<"    �װ��� "<<Getacount()<<" ����30���ӵ�ʱ�䣬����ѡ�Ρ�"<<endl;
    gotoxy(0,5);
    cout<<'\t'<<s<<endl
        <<'\t'<<"  **"<<'\t'<<"1.�޸����롣"<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"**"<<endl
        <<'\t'<<"  **"<<'\t'<<"2.ͨʶ�γ̡�"<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"**"<<endl
        <<'\t'<<"  **"<<'\t'<<"3.��ʼѡ�Ρ�"<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"**"<<endl
        <<'\t'<<"  **"<<'\t'<<"4.���µ��롣"<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"**"<<endl
        <<'\t'<<"  **"<<'\t'<<"0.�˳�ϵͳ��"<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"**"<<endl
        <<'\t'<<"  **"<<'\t'<<"ÿ������ǰ������ּ�Ϊ����ѡ��"<<'\t'<<'\t'<<"**"<<endl
        <<'\t'<<s<<endl<<endl
        <<"==>��ѡ��_:";
    char sa;
    cin>>sa;
    switch(sa-48)    //�˵�����ѡ��
    {
        case 0:exit(0);break;     //�˳�ϵͳ
        case 1:q.Pass_modify(q);break;     //�޸�����
        case 2:{q.disp(q);q.C_main(q);}break;    //��ʾͨʶ�γ�
        case 3:q.X_main(q);break;    //��������Ӳ˵�����ѡ�ο�ʼ
        case 4:Sec_Main();break;     //����ϵͳ��ҳ��
        default:{error_Prompt("���ܴ�������");q.C_main(q);}break;
    }
}

void StudImpl::X_main(StudImpl& q)   //�����Ӳ˵�
{
    M:Sys_display();
    cout<<"��ӭ��������ѡ�Σ�"<<endl<<endl
        <<"    �װ��� "<<Getacount()<<" ��Ŀǰ��ѡ"<<Getsum()<<"ѧ��"<<endl;
    gotoxy(0,5);
    cout<<'\t'<<s<<endl
        <<'\t'<<"  **"<<'\t'<<"1.��ʾ�γ̡�"<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"**"<<endl
        <<'\t'<<"  **"<<'\t'<<"2.ѡ��γ̡�"<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"**"<<endl
        <<'\t'<<"  **"<<'\t'<<"3.ɾ���γ̡�"<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"**"<<endl
        <<'\t'<<"  **"<<'\t'<<"4.���µ��롣"<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"**"<<endl
        <<'\t'<<"  **"<<'\t'<<"5.�˳�ϵͳ��"<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"**"<<endl
        <<'\t'<<"  **"<<'\t'<<"0.������һ����"<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"**"<<endl
        <<'\t'<<"  **"<<'\t'<<"ÿ������ǰ������ּ�Ϊ����ѡ��"<<'\t'<<'\t'<<"**"<<endl
        <<'\t'<<s<<endl<<endl;
    bool aa = q.validation_sum(q);
    if(!aa)
    {
        cout<<endl<<"==>��ѡ��_:";
    }
    char sb;
    cin>>sb;
    switch(sb-48)     //�����˵�����ѡ��
    {
        case 0:q.C_main(q);break;     //������һ��
        case 1:q.display(q);break;    //��ʾѧ����Ϣ
        case 2:q._sech(q,sum);break;  //��ӿγ�
        case 3:q.Modify(q);break;   //ɾ���γ�
        case 4:Sec_Main();break;   //����ϵͳ��ҳ��
        case 5:exit(0);break;     //�˳�ϵͳ
        default:{error_Prompt("���ܴ�������");goto M;}break;
    }
}

void StudImpl::display(StudImpl& q)   //��ʾ��Ϣ
{
    table.disp(q);   //��ʾ��Ϣ
    q.X_main(q);     //���ض����˵�
}

void StudImpl::_search(StudImpl& q)    //�����Ϣ
{
    table._sech(q,sum);
}

double StudImpl::Getsum()     //��ȡѧ��
{
    return sum;
}

void StudImpl::tem(map<string,cour>& tema)   //��ȡ�γ���Ϣ
{
    table._tem(tema);
}

void StudImpl::Modify(StudImpl& q)     //ɾ���û��γ���Ϣ
{
    table.Mod(q,sum);
}

bool StudImpl::validation_sum(StudImpl& q)    //��֤ѧ��
{
    char C;
    if(sum <= 4)
    {
        cout<<"==>��Ŀǰ��ѧ�ֲ���ѧУҪ������ѧ��."<<endl<<endl<<'\t'<<"��F����ѡ��,��T�������κβ�����";
        cin>>C;
        while(true)
        {
            if(C == 'F' || C == 'f')
            {
                q._sech(q,sum);
                return true;
            }
            else if(C == 'T' || C == 't')
            {
                return false;
            }
            cin>>C;
        }
    }
    else if(sum >= 10)
    {
        cout<<"==>��Ŀǰ��ѧ�ָ���ѧУҪ������ѧ�֣�Ϊ�˼�������ѧϰѹ��."<<endl<<endl<<'\t'<<"��F����ɾ��,��T�������κβ�����";
        cin>>C;
        while(true)
        {
            if(C == 'F' || C == 'f')
            {
                q.Modify(q);
                return true;
            }
            else if(C == 'T' || C == 't')
            {
                return false;
            }
            cin>>C;
        }
    }
    else
    {
        return false;
    }
}
