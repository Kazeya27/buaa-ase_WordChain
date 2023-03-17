#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<fstream>
#include <string>
#include "main.h"
using namespace std;
ifstream readFile;


//typedef int(*Func1)(char* words[], int len, char* result[], char head, char tail, char banned, bool enable_loop);
//typedef int(*Func2)(char* words[], int len, char* result[]);
//HMODULE dll = LoadLibrary("core.dll");
//
//Func1 gen_chain_word = (Func1) GetProcAddress(dll, "gen_chain_word");
//Func1 gen_chain_char = (Func1) GetProcAddress(dll, "gen_chain_char");
//Func2 gen_chains_all = (Func2) GetProcAddress(dll, "gen_chains_all");

#pragma comment(lib,"core.lib")
extern "C" __declspec(dllexport) int gen_chain_word(char* words[], int len, char* result[], char head, char tail, char banned, bool enable_loop);
extern "C" __declspec(dllexport) int gen_chain_char(char* words[], int len, char* result[], char head, char tail, char banned, bool enable_loop);
extern "C" __declspec(dllexport) int gen_chains_all(char* words[], int len, char* result[]);

int isletter(char c)
{
    return (c>='a'&&c<='z')||(c>='A'&&c<='Z');
}

vector<string> input()
{
    vector<string> res;
    string s;
    while(getline(readFile,s))
    {
        string now;
        for(int i=0;i<s.size();i++)
        {
            if(!isletter(s[i]))
            {
                if(now.size()>0)
                    res.push_back(now);
                now="";
            }
            else
                now+=(s[i]<'a')?(s[i]+'a'-'A'):s[i];
        }
        if(now.size()>0)
            res.push_back(now);
    }
    readFile.close();
    return res;
}

int check_file(int argc,char* argv[])
{
    string fn;
    bool fileFlag = false;
    for (int j = 1;j<argc && !fileFlag;j++) {
        fn=argv[j];
        for (int i = 0;fn[i];i++) {
            if (fn[i] == '.')
            {
                fileFlag = true;
                break;
            }
        }
    }
    if(!fileFlag)
    {
        cerr <<"please select a file" << endl;
        return FILE_NOT_GIVEN;
    }

    if(fn.size()<=4||fn.substr(fn.size()-4)!=".txt")
    {
        cerr <<"not .txt file!" << endl;
        return FILE_TYPE_WRONG;
    }
    readFile.open(argv[argc-1], ios::in);
    if(!readFile.is_open())
    {
        cerr <<"open file failed!" << endl;
        return FILE_NOT_EXIST;
    }
    return 0;
}
int arg[10];
int checkp(int x)
{
    if(x==1)
    {
        for(int i=1;i<=7;i++)
            if(arg[i]==1) {
                return PARAM_CONFLICT;
            }

        return 0;
    }
    if(x==2||x==3)
    {
        if(arg[1]==1||arg[2]==1||arg[3]==1) {
            return PARAM_CONFLICT;
        }

        return 0;
    }
    if(arg[1]==1||arg[x]==1)
        return PARAM_CONFLICT;
    return 0;
}
int checkz(char* c)
{
    int len=strlen(c);
    if(len!=1)
        return PARAM_FORMAT;
    if(!isletter(c[0]))
        return PARAM_FORMAT;
    return 0;
}
char start='\0',ed='\0',banned='\0';
int op=-1,loop=0;

int read_para(int argc,char *argv[],int* qall)
{
    bool flagH = false,flagT = false,flagJ = false; // 记录-h,-t,-j参数是否已经出现过
    for(int i=1;i<argc-1;i++)                       // 遍历参数列表
    {
        string ag=argv[i];
        if(ag=="-w")                                // -w参数
        {
            if(checkp(2)<0)                      // 异常检测
                return PARAM_CONFLICT;              // 返回异常码
            arg[2]=1;                               // 记录已有的参数
            op=0;                                   // 记录操作方法
        }
        else if(ag=="-c")
        {
            if(checkp(3)<0)
                return PARAM_CONFLICT;
            arg[3]=1;
            op=1;
        }
        else if(ag=="-h")
        {
            if (flagH) {
                return PARAM_DUPLICATE;
            }
            if(checkp(4)<0)
                return PARAM_CONFLICT;
            arg[4]=1;
            i++;
            int res=checkz(argv[i]);
            if(res<0)
                return res;
            start=argv[i][0];
            flagH = true;
        }
        else if(ag=="-t")
        {
            if (flagT) {
                return PARAM_DUPLICATE;
            }
            if(checkp(5)<0)
                return PARAM_CONFLICT;
            arg[5]=1;
            i++;
            int res=checkz(argv[i]);
            if(res<0)
                return res;
            ed=argv[i][0];
            flagT = true;
        }
        else if(ag=="-j")
        {
            if (flagJ) {
                return PARAM_DUPLICATE;
            }
            if(checkp(6)<0)
                return PARAM_CONFLICT;
            arg[6]=1;
            i++;
            int res=checkz(argv[i]);
            if(res<0)
                return res;
            banned=argv[i][0];
            flagJ = true;
        }
        else if(ag=="-r")
        {
            if(checkp(7)<0)
                return PARAM_CONFLICT;
            arg[7]=1;
            loop=1;
        }
        else if(ag=="-n")
        {
            if(checkp(1)<0)
                return PARAM_CONFLICT;
            arg[1]=1;
            *qall=1;
        }
        else
        {
            return PARAM_UNDEFINED;
        }
    }
    if(*qall==0&&op==-1)
        return PARAM_LACK;
    return 0;
}

void print_ans(int len,char* result[],int operate)
{
    ofstream fout("solution.txt");
    if(operate==1)
        fout<<len<<"\n";
    for(int i=0;i<len;i++)
        fout<<result[i]<<"\n";
    fout.close();
}

int test_main(int argc,char* argv[])
{
    char* words[20010];
    char* result[20010];
    start='\0';
    ed='\0';
    banned='\0';
    op=-1;
    loop=0;
    int qall = 0;
    for (int i = 0;i<10;i++)
        arg[i] = 0;
    int res=check_file(argc,argv);
    if(res<0)
        return res;
    res=read_para(argc,argv,&qall);
    if(res<0) {
        if (res == PARAM_CONFLICT) {
            cerr << "selected parameters conflict" << endl;
        }
        else if (res == PARAM_DUPLICATE) {
            cerr << "duplicate head/tail/reject letter" << endl;
        }
        else if (res == PARAM_UNDEFINED) {
            cerr << "undefined parameter!" << endl;
        }
        return res;
    }

    vector<string> all_str=input();
    int len,reslen;
    len=all_str.size();
    for(int i=0;i<len;i++)
    {
        words[i]=new char[all_str[i].size()*sizeof(char)];
        for(int j=0;j<all_str[i].size();j++)
            words[i][j]=all_str[i][j];
        words[i][all_str[i].size()]='\0';
    }

    if(qall==1)
    {
        reslen=gen_chains_all(words,len,result);
        if(reslen == WORD_CIRCLE) {
            cerr << "exist word circle" << endl;
            return reslen;
        }
        else if (reslen > 20000) {
            cerr << "result too long" << endl;
            return RESULT_TOO_LONG;
        }
        print_ans(reslen,result,1);
        return 0;
    }
    if(op==0)
    {
        reslen=gen_chain_word(words,len,  result,  start,  ed, banned,loop);
    }
    else
    {
        reslen=gen_chain_char(words,len,  result,  start,  ed, banned,loop);
    }
    if(reslen == WORD_CIRCLE) {
        cerr << "exist word circle" << endl;
        return reslen;
    }
    print_ans(reslen,result,0);
    return 0;
}
