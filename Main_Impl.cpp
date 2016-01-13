#include <string>
#include <iomanip>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "Stuclass.h"
#include "Mainfunc.h"


const string s1 = "################################################################################";     //页面显示函数变量元素
const string s2 = "  ********************************************************";
const string s3 = "  **    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~     **";

static int a = 0;   //静态变量用于读取文件流中信息
static int b = 0;
static int c = 0;

void pass_disply(string ac)    //修改密码界面
{
    Sys_display();
    cout<<"亲爱的 "<<ac<<" 目前您正在修改密码"<<endl;
}

void error_Prompt(string ss)   //错误信息提示
{
    system("cls");
    gotoxy(3,12);
    cout<<"==>请正确输入"<<ss<<"！请按任意键继续_ _ _";
    getch();
    system("cls");
}

void gotoxy(int x,int y)    //光标定位函数
{
    COORD coord;
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void Main_display()     //系统主界面信息
{
    cout<<s1<<endl
        <<'\t'<<'\t'<<'\t'<<"   "
        <<"天津科技大学选课系统"<<endl
        <<"选课说明："<<endl
        <<'\n'<<"  一、选课范围"<<'\n'<<'\t'<<"201*~201*学年第*学期开设的选修课及体育课"<<endl
        <<"  二、选课时间"<<'\n'<<'\t'<<"**校区选课时间为**月**日，**校区选课时间为**月**日"<<endl
        <<"  三、注意事项"<<endl
        <<'\t'<<"1.登入账号为学号，初始化密码为2013，您登入后可以修改您的登入密码。"<<endl
        <<'\t'<<"2.注意每学期所需要选修的最低学分和最高学分。"<<endl
        <<'\t'<<"3.体育课在每学期必选一门课程，公共选修最多不能超过4科（包括4科）。"<<endl<<endl
        <<s1<<endl
        <<'\t'<<s2<<endl
        <<'\t'<<"  **"<<'\t'<<"  Loge In Student Course Selection System"<<'\t'<<"**"<<endl
        <<'\t'<<s3<<endl
        <<'\t'<<"  **      Acount:"<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"**"<<endl
        <<'\t'<<"  **    Password:"<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"**"<<endl
        <<'\t'<<s2<<endl
        <<endl
        <<'\t'<<'\t'<<'\t'<<"@2015  JY  玄ICP证010619号";
}

void Storage_pass(map<string,string> as)    //保存密码信息
{
    char* FileNameOut = "e:/Acount.csv";
    ofstream FileOutput;
    FileOutput.open( FileNameOut );
    if (!FileOutput)
    {
        cout << "文件: " << FileNameOut
            << " 存档失败!"  << endl;
            exit(1);
    }
    for(auto it= as.cbegin();it != as.cend();it++)    //遍历容器所有信息
        FileOutput<<it->first<<','<<it->second<<endl;
    FileOutput.close();
}

void save_cour(map<string,cour> tem,string acou)    //保存学生课程信息
{
    string FileNameOut = "e:/";
    FileNameOut += acou;
    FileNameOut += ".csv";
    ofstream FileOutput;
    FileOutput.open( FileNameOut.c_str() );
    if (!FileOutput)
    {
        cout << "文件: " << FileNameOut
            << " 存档失败!"  << endl;
            exit(1);
    }
    for(auto it= tem.cbegin();it != tem.cend();it++)   //遍历容器中的所有元素
        FileOutput<<it->second.KC_numb<<','<<it->second.C_name<<','<<it->second.C_Teacher_name<<','<<it->second.C_score<<','<<it->second.C_room<<','<<it->second.C_time<<endl;
    FileOutput.close();
}

void read_acount(ifstream &is, ifstream &iss,vector<A>& test,vector<cour>& tests)    //获取系统用户信息及课程信息
{
    A Aa;
    cour cs;
    string value;
    while(getline(is,value))
    {
        istringstream sin(value);
        string field;
        while(getline(sin,field,','))
        {
            //cout<<field<<endl;
            if(a == 0)
            {
                Aa.aco = field;
                a = 1;
            }
            else
            {
                Aa.pas = field;
                a = 0;
            }
        }
        test.push_back(Aa);
    }
    string values;
    while(getline(iss,values))
    {
        istringstream sin(values);
        string fields;
        while(getline(sin,fields,','))
        {
            switch(b)
            {
                case 0:{cs.KC_numb = fields; b = 1;}break;
                case 1:{cs.C_name = fields; b = 2;}break;
                case 2:{cs.C_Teacher_name = fields; b = 3;}break;
                case 3:{cs.C_score = fields; b = 4;}break;
                case 4:{cs.C_room = fields; b = 5;}break;
                case 5:{cs.C_time = fields; b = 0;}break;
                default:break;
            }
        }
        tests.push_back(cs);
    }
}

void ini_acount_cour(ifstream &iss,vector<cour>&tests,double& sum)     //获取学生课程信息
{
    cour cs;        //创建临时容器元素
    string values;
    while(getline(iss,values))     //行行读取流中信息
    {
        istringstream sin(values);
        string fields;
        while(getline(sin,fields,','))      //获取每行中信息
        {
            switch(c)
            {
                case 0:{cs.KC_numb = fields; c = 1;}break;
                case 1:{cs.C_name = fields; c = 2;}break;
                case 2:{cs.C_Teacher_name = fields; c = 3;}break;
                case 3:{cs.C_score = fields;string sss = fields;const char* o = sss.c_str();sum += atof(o); c = 4;}break;       //累加该学生学分
                case 4:{cs.C_room = fields; c = 5;}break;
                case 5:{cs.C_time = fields; c = 0;}break;
                default:break;
            }
        }
        tests.push_back(cs);
    }
}

void tem_cour_disp(map<string,cour> tem)     //临时课程信息函数
{
    system("cls");
    Sys_display();
    cout<<setw(9)<<'-'<<"----------------------------------------------------"<<endl;
    cout<<setw(9)<<'|'<<setw(11)<<"课程号"<<'|'<<setw(11)<<"课程"<<'|'<<setw(6)<<"教师"<<'|'<<setw(4)<<"学分"<<'|'<<setw(10)<<"地点"<<'|'<<setw(4)<<"时间"<<'|'<<endl;
    cout<<setw(9)<<'='<<"===================================================="<<endl;
    auto it = tem.cbegin();
    for(;it != tem.cend();it++)
    {
        cout<<setw(9)<<'|'<<setw(11)<<it->second.KC_numb<<'|'<<setw(11)<<it->second.C_name<<'|'<<setw(6)<<it->second.C_Teacher_name<<'|'<<setw(4)<<it->second.C_score<<'|'<<setw(10)<<it->second.C_room<<'|'<<setw(4)<<it->second.C_time<<'|'<<endl
            <<setw(9)<<'-'<<"----------------------------------------------------"<<endl;
    }
}

void Sys_display()         //系统界面标题函数
{
    system("cls");
    cout<<'\t'<<'\t'<<'\t'<<"   "
        <<"天津科技大学选课系统"<<endl;
}

void Sec_Main()   //系统主界面
{
    system("cls");
    Main_display();   //打印主界页面
    int d = 0;
    vector<A> A;
    vector<cour> Cs;
    vector<cour> Xc;
    ifstream infile("e:/Acount.csv");      //创建用户信息文件流
    ifstream ini("e:/course.csv");         //创建课程信息文件流
    read_acount(infile, ini, A, Cs);       //将文件流信息分别存储到相应变量中
    infile.close();     //关闭文件流
    ini.close();        //关闭文件流
    gotoxy(25,19);      //光标定位
    string ac;
    double _sum = 0;
    cin>>ac;
    for(auto r : A)
        if(r.aco == ac)
            d=1;
    if(d)           //判断用户账户是否在数据库中
    {
        string ord = "e:/";
        ord += ac;
        ord += ".csv";
        ifstream ini_cour;             //创建用户课程信息流
        ini_cour.open( ord.c_str() );
        if (ini_cour)            //判断数据库中是否有用户课程信息
        {
            ini_acount_cour(ini_cour,Xc,_sum);
            ini_cour.close();
        }
        StudImpl q(ac,A,Cs,Xc,_sum);       //创建学生类对象
        if(q.Reflect(q))         //验证账号和密码
            q.C_main(q);         //进入一级子菜单
    }
    else
    {
        system("cls");
        gotoxy(3,12);
        cout<<"==>抱歉！数据库里未有"<<ac<<"信息请先联系管理员！请按任意键继续_ _ _";
        getch();
        system("cls");
        Sec_Main();       //回调系统主界面
    }
}
