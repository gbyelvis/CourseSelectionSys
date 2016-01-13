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

map<string,cour> temporary;   //存取信息临时变量

const string s = "  ********************************************************";

StuPassw::StuPassw(string ac,vector<A> Aa):Acount(ac)       //初始化用户密码类
{
    for(auto r : Aa)
    {
        wm.insert(make_pair(r.aco,r.pas));       //插入元素
    }
}

bool StuPassw::Reflect(StudImpl& q) const     //验证用户账户及其密码
{
    string ac = "";
    if(c)          //账户输入错误后重新输入
    {
        gotoxy(25,19);
        cin>>ac;
    }
    string pass;
    gotoxy(25,20);
    cin>>pass;
    auto map_it = wm.find(Acount);              //find函数找到该用户信息
    if(map_it != wm.cend() && pass == map_it->second)    //进行验证
    {
        system("cls");
        return true;
    }
    else          //重新验证
    {
        error_Prompt("账号和密码");
        Main_display();
        c = 1;
        q.Reflect(q);
    }
    return true;
}

void StuPassw::Pass_modify(StudImpl& q)        //密码修改函数
{
    N:pass_disply(Acount);
    auto map_pass = wm.find(Acount);      //find函数找到该用户信息
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
    if(map_pass->second != s3)    //验证原密码
    {
        error_Prompt("原密码");    //错误信息提示
        goto N;
    }
    else if(_s3 != _s3_)     //验证两次新密码输入是否正确
    {
        error_Prompt("新密码");
        goto N;
    }
    else
    {
        map_pass->second = _s3;           //修改用户密码
        Storage_pass(wm);                 //保存系统密码文件
        system("cls");
        gotoxy(3,12);
        cout<<"==>修改成功！请按任意键继续_ _ _";
        getch();
        system("cls");
        q.C_main(q);        //返回一级子菜单
    }
}

string StuPassw::Getacount()      //获取用户账户
{
    return Acount;
}

void Course::disp(StudImpl& q)     //课程信息函数
{
    system("cls");
    Sys_display();
    cout<<setw(9)<<'-'<<"----------------------------------------------------"<<endl;
    cout<<setw(9)<<'|'<<setw(11)<<"课程号"<<'|'<<setw(11)<<"课程"<<'|'<<setw(6)<<"教师"<<'|'<<setw(4)<<"学分"<<'|'<<setw(10)<<"地点"<<'|'<<setw(4)<<"时间"<<'|'<<endl;
    cout<<setw(9)<<'='<<"===================================================="<<endl;
    auto it = _course.cbegin();
    for(;it != _course.cend();it++)
    {
        cout<<setw(9)<<'|'<<setw(11)<<it->second.KC_numb<<'|'<<setw(11)<<it->second.C_name<<'|'<<setw(6)<<it->second.C_Teacher_name<<'|'<<setw(4)<<it->second.C_score<<'|'<<setw(10)<<it->second.C_room<<'|'<<setw(4)<<it->second.C_time<<'|'<<endl
            <<setw(9)<<'-'<<"----------------------------------------------------"<<endl;
    }
    cout<<"==>按任意键返回上一级_";
    getch();
}

void Course::_sech(StudImpl& q,double& sum)    //添加学生课程信息
{
    Sys_display();         //打印页面题头
    cout<<endl<<"注意：输入\‘#\’为退出\“选择课程\”,输入\‘@\’为显示\“课程信息\”"<<endl
        <<'\t'<<"（请只显示课程一次，以防止之前选过的课程未被保存）"<<endl<<endl
        <<'\t'<<"请输入课程号_：";
    q.tem(temporary);          //将原先的课程存储进temporary
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
                    if(ita->second.C_time == itt->second.C_time || ita->second.KC_numb == itt->second.KC_numb)  //验证时间是否不同及课程号
                    {
                        g = 0;
                        cout<<"您重复选课，或者课程时间有冲突"<<endl
                            <<'\t'<<"请输入课程号_：";
                        break;
                    }
                if(g)
                {   temporary.insert(make_pair(a1,itt->second));    //添加单条课程信息
                    string sss = itt->second.C_score;           //累加学分
                    const char* o = sss.c_str();
                    sum += atof(o);
                    cout<<"保存成功！"<<endl
                        <<'\t'<<"请输入课程号_：";
                }
            }
            else
                {cout<<"保存失败！"<<endl<<'\t'<<"请输入课程号_：";}
        }
        else
        {q.disp(q);q._sech(q,sum);}
        cin>>a1;
    }
    q.tem(temporary);          //将原先的课程存储进temporary
    tem_cour_disp(temporary);   //显示课程信息
    char c;
    cout<<endl
    <<"==>保存按\'Y\',取消按\'N\'：";
    cin>>c;
    while(true)
    {
        if(c == 'Y' || c == 'y')
        {
            save_cour(temporary,q.Getacount());     //保存学生课程信息
            cout<<"保存成功"<<endl
                <<endl<<"==>按任意键返回上一级_";
            break;
        }
        else if(c == 'N' || c =='n')
        {
            cout<<"未保存"
                <<endl<<"==>按任意键返回上一级_";
            break;
        }
        cin>>c;
    }
    getch();
    q.X_main(q);      //返回第二级子菜单
}

void Course::_tem(map<string,cour> &tem)              //课程信息及时交互
{
    for(auto it_ = _course.cbegin();it_ != _course.cend();it_++)
        tem.insert(make_pair(it_->first,it_->second));
    for(auto _it_ = tem.cbegin();_it_ != tem.cend();_it_++)
        _course.insert(make_pair(_it_->first,_it_->second));

}

void Course::Mod(StudImpl& q,double& sum)   //删除课程
{
    Sys_display();
    cout<<endl<<"注意：输入\‘#\’为退出\“删除课程\”,输入\‘@\’为显示\“课程信息\”"<<endl
        <<'\t'<<"（请只显示课程一次，以防止之前删除过的课程未被保存）"<<endl<<endl
        <<'\t'<<"请输入课程号_：";
    string a1;
    cin>>a1;
    while(a1 != "#")
    {
        if(a1 != "@")
        {
            auto itt = _course.find(a1);
            if(itt != _course.cend())
            {
                _course.erase(itt);               //删除单条课程信息
                string sss = itt->second.C_score;     //累减学分
                const char* o = sss.c_str();
                sum -= atof(o);
                cout<<"删除成功！"<<endl
                    <<'\t'<<"请输入课程号_：";
            }
            else
                {cout<<"删除失败！"<<endl<<'\t'<<"请输入课程号_：";}
        }
        else
        {q.disp(q);q._sech(q,sum);}
        cin>>a1;
    }
    temporary.clear();      //清空临时变量
    temporary = _course;    //拷贝变量
    tem_cour_disp(temporary);   //显示课程信息
    //q.tem(temporary);
    char c;
    cout<<endl
    <<"==>保存按\'Y\',取消按\'N\'：";
    cin>>c;
    while(true)
    {
        if(c == 'Y' || c == 'y')
        {
            save_cour(temporary,q.Getacount());   //保存学生课程信息
            cout<<"保存成功"<<endl
                <<endl<<"==>按任意键返回上一级_";
            break;
        }
        else if(c == 'N' || c =='n')
        {
            cout<<"未保存"
                <<endl<<"==>按任意键返回上一级_";
            break;
        }
        cin>>c;
    }
    getch();
    q.X_main(q);     //返回第二级子菜单
}

Course::Course(vector<cour> cou)      //初始化课程信息类
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

void StudImpl::C_main(StudImpl& q)   //一级子菜单
{
    Sys_display();
    cout<<"欢迎您，进行选课！"<<endl<<endl
        <<"    亲爱的 "<<Getacount()<<" 您有30分钟的时间，进行选课。"<<endl;
    gotoxy(0,5);
    cout<<'\t'<<s<<endl
        <<'\t'<<"  **"<<'\t'<<"1.修改密码。"<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"**"<<endl
        <<'\t'<<"  **"<<'\t'<<"2.通识课程。"<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"**"<<endl
        <<'\t'<<"  **"<<'\t'<<"3.开始选课。"<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"**"<<endl
        <<'\t'<<"  **"<<'\t'<<"4.重新登入。"<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"**"<<endl
        <<'\t'<<"  **"<<'\t'<<"0.退出系统。"<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"**"<<endl
        <<'\t'<<"  **"<<'\t'<<"每个功能前面的数字即为功能选择。"<<'\t'<<'\t'<<"**"<<endl
        <<'\t'<<s<<endl<<endl
        <<"==>请选择_:";
    char sa;
    cin>>sa;
    switch(sa-48)    //菜单功能选择
    {
        case 0:exit(0);break;     //退出系统
        case 1:q.Pass_modify(q);break;     //修改密码
        case 2:{q.disp(q);q.C_main(q);}break;    //显示通识课程
        case 3:q.X_main(q);break;    //进入二级子菜单，即选课开始
        case 4:Sec_Main();break;     //返回系统主页面
        default:{error_Prompt("功能代表数字");q.C_main(q);}break;
    }
}

void StudImpl::X_main(StudImpl& q)   //二级子菜单
{
    M:Sys_display();
    cout<<"欢迎您，进行选课！"<<endl<<endl
        <<"    亲爱的 "<<Getacount()<<" 您目前已选"<<Getsum()<<"学分"<<endl;
    gotoxy(0,5);
    cout<<'\t'<<s<<endl
        <<'\t'<<"  **"<<'\t'<<"1.显示课程。"<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"**"<<endl
        <<'\t'<<"  **"<<'\t'<<"2.选择课程。"<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"**"<<endl
        <<'\t'<<"  **"<<'\t'<<"3.删除课程。"<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"**"<<endl
        <<'\t'<<"  **"<<'\t'<<"4.重新登入。"<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"**"<<endl
        <<'\t'<<"  **"<<'\t'<<"5.退出系统。"<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"**"<<endl
        <<'\t'<<"  **"<<'\t'<<"0.返回上一级。"<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"**"<<endl
        <<'\t'<<"  **"<<'\t'<<"每个功能前面的数字即为功能选择。"<<'\t'<<'\t'<<"**"<<endl
        <<'\t'<<s<<endl<<endl;
    bool aa = q.validation_sum(q);
    if(!aa)
    {
        cout<<endl<<"==>请选择_:";
    }
    char sb;
    cin>>sb;
    switch(sb-48)     //二级菜单功能选择
    {
        case 0:q.C_main(q);break;     //返回上一级
        case 1:q.display(q);break;    //显示学生信息
        case 2:q._sech(q,sum);break;  //添加课程
        case 3:q.Modify(q);break;   //删除课程
        case 4:Sec_Main();break;   //返回系统主页面
        case 5:exit(0);break;     //退出系统
        default:{error_Prompt("功能代表数字");goto M;}break;
    }
}

void StudImpl::display(StudImpl& q)   //显示信息
{
    table.disp(q);   //显示信息
    q.X_main(q);     //返回二级菜单
}

void StudImpl::_search(StudImpl& q)    //添加信息
{
    table._sech(q,sum);
}

double StudImpl::Getsum()     //获取学分
{
    return sum;
}

void StudImpl::tem(map<string,cour>& tema)   //存取课程信息
{
    table._tem(tema);
}

void StudImpl::Modify(StudImpl& q)     //删除用户课程信息
{
    table.Mod(q,sum);
}

bool StudImpl::validation_sum(StudImpl& q)    //验证学分
{
    char C;
    if(sum <= 4)
    {
        cout<<"==>您目前的学分不够学校要求的最低学分."<<endl<<endl<<'\t'<<"按F进行选课,按T不进行任何操作。";
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
        cout<<"==>您目前的学分高于学校要求的最高学分，为了减轻您的学习压力."<<endl<<endl<<'\t'<<"按F进行删除,按T不进行任何操作。";
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
