#include <string>
#include <iomanip>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "Stuclass.h"
#include "Mainfunc.h"


const string s1 = "################################################################################";     //ҳ����ʾ��������Ԫ��
const string s2 = "  ********************************************************";
const string s3 = "  **    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~     **";

static int a = 0;   //��̬�������ڶ�ȡ�ļ�������Ϣ
static int b = 0;
static int c = 0;

void pass_disply(string ac)    //�޸��������
{
    Sys_display();
    cout<<"�װ��� "<<ac<<" Ŀǰ�������޸�����"<<endl;
}

void error_Prompt(string ss)   //������Ϣ��ʾ
{
    system("cls");
    gotoxy(3,12);
    cout<<"==>����ȷ����"<<ss<<"���밴���������_ _ _";
    getch();
    system("cls");
}

void gotoxy(int x,int y)    //��궨λ����
{
    COORD coord;
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void Main_display()     //ϵͳ��������Ϣ
{
    cout<<s1<<endl
        <<'\t'<<'\t'<<'\t'<<"   "
        <<"���Ƽ���ѧѡ��ϵͳ"<<endl
        <<"ѡ��˵����"<<endl
        <<'\n'<<"  һ��ѡ�η�Χ"<<'\n'<<'\t'<<"201*~201*ѧ���*ѧ�ڿ����ѡ�޿μ�������"<<endl
        <<"  ����ѡ��ʱ��"<<'\n'<<'\t'<<"**У��ѡ��ʱ��Ϊ**��**�գ�**У��ѡ��ʱ��Ϊ**��**��"<<endl
        <<"  ����ע������"<<endl
        <<'\t'<<"1.�����˺�Ϊѧ�ţ���ʼ������Ϊ2013�������������޸����ĵ������롣"<<endl
        <<'\t'<<"2.ע��ÿѧ������Ҫѡ�޵����ѧ�ֺ����ѧ�֡�"<<endl
        <<'\t'<<"3.��������ÿѧ�ڱ�ѡһ�ſγ̣�����ѡ����಻�ܳ���4�ƣ�����4�ƣ���"<<endl<<endl
        <<s1<<endl
        <<'\t'<<s2<<endl
        <<'\t'<<"  **"<<'\t'<<"  Loge In Student Course Selection System"<<'\t'<<"**"<<endl
        <<'\t'<<s3<<endl
        <<'\t'<<"  **      Acount:"<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"**"<<endl
        <<'\t'<<"  **    Password:"<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"**"<<endl
        <<'\t'<<s2<<endl
        <<endl
        <<'\t'<<'\t'<<'\t'<<"@2015  JY  ��ICP֤010619��";
}

void Storage_pass(map<string,string> as)    //����������Ϣ
{
    char* FileNameOut = "e:/Acount.csv";
    ofstream FileOutput;
    FileOutput.open( FileNameOut );
    if (!FileOutput)
    {
        cout << "�ļ�: " << FileNameOut
            << " �浵ʧ��!"  << endl;
            exit(1);
    }
    for(auto it= as.cbegin();it != as.cend();it++)    //��������������Ϣ
        FileOutput<<it->first<<','<<it->second<<endl;
    FileOutput.close();
}

void save_cour(map<string,cour> tem,string acou)    //����ѧ���γ���Ϣ
{
    string FileNameOut = "e:/";
    FileNameOut += acou;
    FileNameOut += ".csv";
    ofstream FileOutput;
    FileOutput.open( FileNameOut.c_str() );
    if (!FileOutput)
    {
        cout << "�ļ�: " << FileNameOut
            << " �浵ʧ��!"  << endl;
            exit(1);
    }
    for(auto it= tem.cbegin();it != tem.cend();it++)   //���������е�����Ԫ��
        FileOutput<<it->second.KC_numb<<','<<it->second.C_name<<','<<it->second.C_Teacher_name<<','<<it->second.C_score<<','<<it->second.C_room<<','<<it->second.C_time<<endl;
    FileOutput.close();
}

void read_acount(ifstream &is, ifstream &iss,vector<A>& test,vector<cour>& tests)    //��ȡϵͳ�û���Ϣ���γ���Ϣ
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

void ini_acount_cour(ifstream &iss,vector<cour>&tests,double& sum)     //��ȡѧ���γ���Ϣ
{
    cour cs;        //������ʱ����Ԫ��
    string values;
    while(getline(iss,values))     //���ж�ȡ������Ϣ
    {
        istringstream sin(values);
        string fields;
        while(getline(sin,fields,','))      //��ȡÿ������Ϣ
        {
            switch(c)
            {
                case 0:{cs.KC_numb = fields; c = 1;}break;
                case 1:{cs.C_name = fields; c = 2;}break;
                case 2:{cs.C_Teacher_name = fields; c = 3;}break;
                case 3:{cs.C_score = fields;string sss = fields;const char* o = sss.c_str();sum += atof(o); c = 4;}break;       //�ۼӸ�ѧ��ѧ��
                case 4:{cs.C_room = fields; c = 5;}break;
                case 5:{cs.C_time = fields; c = 0;}break;
                default:break;
            }
        }
        tests.push_back(cs);
    }
}

void tem_cour_disp(map<string,cour> tem)     //��ʱ�γ���Ϣ����
{
    system("cls");
    Sys_display();
    cout<<setw(9)<<'-'<<"----------------------------------------------------"<<endl;
    cout<<setw(9)<<'|'<<setw(11)<<"�γ̺�"<<'|'<<setw(11)<<"�γ�"<<'|'<<setw(6)<<"��ʦ"<<'|'<<setw(4)<<"ѧ��"<<'|'<<setw(10)<<"�ص�"<<'|'<<setw(4)<<"ʱ��"<<'|'<<endl;
    cout<<setw(9)<<'='<<"===================================================="<<endl;
    auto it = tem.cbegin();
    for(;it != tem.cend();it++)
    {
        cout<<setw(9)<<'|'<<setw(11)<<it->second.KC_numb<<'|'<<setw(11)<<it->second.C_name<<'|'<<setw(6)<<it->second.C_Teacher_name<<'|'<<setw(4)<<it->second.C_score<<'|'<<setw(10)<<it->second.C_room<<'|'<<setw(4)<<it->second.C_time<<'|'<<endl
            <<setw(9)<<'-'<<"----------------------------------------------------"<<endl;
    }
}

void Sys_display()         //ϵͳ������⺯��
{
    system("cls");
    cout<<'\t'<<'\t'<<'\t'<<"   "
        <<"���Ƽ���ѧѡ��ϵͳ"<<endl;
}

void Sec_Main()   //ϵͳ������
{
    system("cls");
    Main_display();   //��ӡ����ҳ��
    int d = 0;
    vector<A> A;
    vector<cour> Cs;
    vector<cour> Xc;
    ifstream infile("e:/Acount.csv");      //�����û���Ϣ�ļ���
    ifstream ini("e:/course.csv");         //�����γ���Ϣ�ļ���
    read_acount(infile, ini, A, Cs);       //���ļ�����Ϣ�ֱ�洢����Ӧ������
    infile.close();     //�ر��ļ���
    ini.close();        //�ر��ļ���
    gotoxy(25,19);      //��궨λ
    string ac;
    double _sum = 0;
    cin>>ac;
    for(auto r : A)
        if(r.aco == ac)
            d=1;
    if(d)           //�ж��û��˻��Ƿ������ݿ���
    {
        string ord = "e:/";
        ord += ac;
        ord += ".csv";
        ifstream ini_cour;             //�����û��γ���Ϣ��
        ini_cour.open( ord.c_str() );
        if (ini_cour)            //�ж����ݿ����Ƿ����û��γ���Ϣ
        {
            ini_acount_cour(ini_cour,Xc,_sum);
            ini_cour.close();
        }
        StudImpl q(ac,A,Cs,Xc,_sum);       //����ѧ�������
        if(q.Reflect(q))         //��֤�˺ź�����
            q.C_main(q);         //����һ���Ӳ˵�
    }
    else
    {
        system("cls");
        gotoxy(3,12);
        cout<<"==>��Ǹ�����ݿ���δ��"<<ac<<"��Ϣ������ϵ����Ա���밴���������_ _ _";
        getch();
        system("cls");
        Sec_Main();       //�ص�ϵͳ������
    }
}
