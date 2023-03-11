#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<fstream>
#include<set>
#include<string>
using namespace std;
ifstream readFile;
ofstream fout("output.txt");
// diao yong dll
#pragma comment(lib, "../bin/WordChain.lib")
// shengming hanshu
extern "C" __declspec(dllexport) int gen_chain_word(char* words[], int len, char* result[], char head, char tail, char banned, bool enable_loop);
extern "C" __declspec(dllexport) int gen_chain_char(char* words[], int len, char* result[], char head, char tail, char banned, bool enable_loop);
extern "C" __declspec(dllexport) int gen_chains_all(char* words[], int len, char* result[]);
int isletter(char c)
{
    return (c>='a'&&c<='z')||(c>='A'&&c<='Z');
}
int issmall(char c)
{
    return (c>='a'&&c<='z');
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
                if(now.size()>0) res.push_back(now);
                now="";
            }
            else now+=(s[i]<'a')?(s[i]+'a'-'A'):s[i];
        }
        if(now.size()>0) res.push_back(now);
    }
    return res;
}
int check_file(int argc,char* argv[])
{
    if(argc<2)
    {
        cout<<"too few para!";
        return -9;
    }
    string fn=argv[argc-1];
    if(fn.size()<=4||fn.substr(fn.size()-4)!=".txt")
    {
        cout<<"not .txt file!";
        return -6;
    }
//    cout << argv[argc-1] << endl;
    readFile.open(argv[argc-1], ios::in);
    if(!readFile.is_open())
    {
        cout<<"open file failed!";
        return -7;
    }
    return 0;
}
int arg[10];
int checkp(int x)
{
    if(x==1)
    {
        for(int i=1;i<=7;i++)
            if(arg[i]==1) return -1;
        return 0;
    }
    if(x==2||x==3)
    {
        if(arg[1]==1||arg[2]==1||arg[3]==1) return -1;
        return 0;
    }
    if(arg[1]==1||arg[x]==1) return -1;
    return 0;
}
int checkz(char* c)
{
    int len=strlen(c);
    if(len!=1) return -4;
    if(!issmall(c[0])) return -4;
    return 0;
}
char start='\0',ed='\0',banned='\0';
int op=-1,loop=0,qall=0;
int read_para(int argc,char *argv[])
{
    for(int i=1;i<argc-1;i++)
    {
        string ag=argv[i];
        if(ag=="-w")
        {
            if(checkp(1)<0) return -1;
            arg[1]=1;
            op=0;
        }
        else if(ag=="-c")
        {
            if(checkp(2)<0) return -1;
            arg[2]=1;
            op=1;
        }
        else if(ag=="-h")
        {
            if(checkp(3)<0) return -1;
            arg[3]=1;
            i++;
            int res=checkz(argv[i]);
            if(res<0) return res;
            start=argv[i][0];
        }
        else if(ag=="-t")
        {
            if(checkp(4)<0) return -1;
            arg[4]=1;
            i++;
            int res=checkz(argv[i]);
            if(res<0) return res;
            ed=argv[i][0];
        }
        else if(ag=="-j")
        {
            if(checkp(5)<0) return -1;
            arg[5]=1;
            i++;
            int res=checkz(argv[i]);
            if(res<0) return res;
            banned=argv[i][0];
        }
        else if(ag=="-r")
        {
            if(checkp(6)<0) return -1;
            arg[6]=1;
            loop=1;
        }
        else if(ag=="-n")
        {
            cout << "模式-n";
            if(checkp(7)<0) return -1;
            arg[7]=1;
            qall=1;
        }
        else
        {
            cout<<"wrong para!";
            return -5;
        }
    }
    if(op==-1) return -2;
    return 0;
}
void print_ans(int len,char* result[],int op)
{
    int i;
    if(op==1) fout<<len<<"\n";
    for(int i=0;i<len;i++) cout<<result[i]<<"\n";
}
char* words[10010];
char* result[10010];

int main(int argc,char* argv[])
{
    int res=check_file(argc,argv);
    if(res<0) return res;
    res=read_para(argc,argv);
    if(res<0) return res;

    vector<string> all_str=input();
    int len,reslen;
    len=all_str.size();
    for(int i=0;i<len;i++)
    {
        words[i]=new char[all_str[i].size()*sizeof(char)];
        for(int j=0;j<all_str[i].size();j++)
            words[i][j]=all_str[i][j];
        words[i][all_str[i].size()]='\0';
        //cout<<words[i]<<"#\n";
    }
    if(qall==1)
    {
        reslen=gen_chains_all(words,len,result);
        if(reslen<0) return reslen;
        print_ans(reslen,result,1);
        return 0;
    }
    if(op==0)
    {
        reslen=gen_chain_word(words,len,  result,  start,  ed, banned,loop);
        if(reslen<0) return reslen;
        print_ans(reslen,result,0);
        return 0;
    }
    else
    {
        reslen=gen_chain_char(words,len,  result,  start,  ed, banned,loop);
        if(reslen<0) return reslen;
        print_ans(reslen,result,0);
        return 0;
    }

}