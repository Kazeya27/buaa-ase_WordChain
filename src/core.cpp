#include "core.h"
#include<iostream>
#include<vector>
#include<set>
#include<queue>
#include<algorithm>

using namespace std;

vector<vector<int> > build_graph(vector<string> str)
{
    int n=str.size();
    vector<vector<int> > g(n,vector<int>());
    vector<int> z(n,0);
    vector<int> zihuan[30];
    for(int i=0;i<n;i++) {
        if(str[i].back()==str[i].front())
        {
            z[i]=1;
            zihuan[str[i].back()-'a'].push_back(i);
        }
    }

    for(int i=0;i<26;i++) {
        sort(zihuan[i].begin(),zihuan[i].end());
    }

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i==j) {
                continue;
            }

            if(str[i].back()==str[j].front())
            {
                int ai=str[i].back()-'a',aj=str[j].back()-'a';
                if(z[i]==1&&z[j]==1) {
                    continue;
                }

                if(z[i]==1)
                {
                    if(zihuan[ai].back()==i) {
                        g[zihuan[ai].back()].push_back(j);
                    }

                }
                else if(z[j]==1)
                {
                    if(zihuan[aj].back()==j) {
                        g[i].push_back(zihuan[aj].front());
                    }

                }
                else {
                    g[i].push_back(j);
                }

            }
        }
    }
    for(int i=0;i<26;i++)
    {
        for(int j=0;j<(int)zihuan[i].size()-1;j++) {
            g[zihuan[i][j]].push_back(zihuan[i][j+1]);
        }

        if(zihuan[i].size()>1) {
            g[zihuan[i].back()].push_back(zihuan[i][0]);
        }

    }
    /*for(int i=0;i<n;i++) cout<<i<<" "<<str[i]<<"\n";
    for(int i=0;i<n;i++)
    {
        for(auto j:g[i]) cout<<j<<" ";
        cout<<endl;
    }*/
    return g;
}
vector<string> get_max(int n,vector<vector<int> > g,vector<string> str,
                       int op,char start,char end,set<char> ban)
//op==0 : max word cnt,op==1 : max character cnt
{
    vector<int> rd(n,0),dp(n,0),pre(n,-1);
    queue<int> q;
    int inf=1<<28;
    for(int i=0;i<n;i++)
    {
        for(auto j:g[i])
            rd[j]++;
        if(op==1)
            dp[i]=str[i].size();
        else
            dp[i]=1;
        if(start!='\0'&&str[i][0]!=start)
            dp[i]=-inf;
        if(ban.find(str[i][0])!=ban.end())
            dp[i]=-inf;
    }
    for(int i=0;i<n;i++)
        if(rd[i]==0)
            q.push(i);
    //for(int i=0;i<n;i++) cout<<dp[i]<<" \n"[i==n-1];
    while(!q.empty())
    {
        int now=q.front();
        q.pop();
        for(auto i:g[now])
        {
            int cd=1;
            if(op==1)
                cd=str[i].size();
            if(ban.find(str[i][0])==ban.end()&&dp[i]<dp[now]+cd)
            {
                dp[i]=dp[now]+cd;
                pre[i]=now;
            }
            rd[i]--;
            if(rd[i]==0)
                q.push(i);
        }
    }
    //for(int i=0;i<n;i++) cout<<dp[i]<<" \n"[i==n-1];
    int pos=0,mx=0;
    for(int i=0;i<n;i++)
        if(dp[i]>mx&&(end=='\0'||str[i].back()==end))
            mx=dp[i],pos=i;

    //cout<<mx<<" "<<pos<<"\n";
    vector<string> res;
    if(mx==0)
        return res;
    while(pos!=-1)
    {
        res.push_back(str[pos]);
        pos=pre[pos];
    }
    reverse(res.begin(),res.end());
    return res;
}
int check(int n,vector<vector<int> > g)
{
    int cnt=0;
    vector<int> rd(n,0);
    queue<int> q;
    for(int i=0;i<n;i++)
    {
        for(auto j:g[i])
            rd[j]++;
    }
    for(int i=0;i<n;i++)
        if(rd[i]==0)
            q.push(i);
    while(!q.empty())
    {
        int now=q.front();
        q.pop();
        cnt++;
        for(auto i:g[now])
        {
            rd[i]--;
            if(rd[i]==0)
                q.push(i);
        }
    }
    return cnt==n;
}
vector<vector<string> > all_list;
vector<string> ans_circle;
vector<string> now;
vector<int> vis;
int now_max,char_len;

void get_all(int n,vector<vector<int> > g,vector<string> str,int x)
{
    if(x==-1)
    {
        for(int i=0;i<n;i++)
        {
            now.push_back(str[i]);
            get_all(n,g,str,i);
            now.pop_back();
        }
        return;
    }
    if(now.size()>1)
        all_list.push_back(now);
    for(auto i:g[x])
    {
        now.push_back(str[i]);
        get_all(n,g,str,i);
        now.pop_back();
    }
}
void circle_max(int n,int x,vector<vector<int> > g,vector<string> str,
                int op,char start,char end,set<char> ban)
{
    //cout<<x<<" ";
    if(x==-1)
    {
        for(int i=0;i<n;i++)
        {
            if(start!='\0'&&start!=str[i][0])
                continue;
            now.push_back(str[i]);
            char_len+=str[i].length();
            circle_max(n,i,g,str,op,start,end,ban);
            char_len-=str[i].length();
            now.pop_back();
        }
        return;
    }
    if(ban.find(str[x][0])!=ban.end())
        return;
    vis[x]=1;
    int len;
    if(op==0)
        len=now.size();
    else
        len=char_len;
    if(len>max(now_max,1))
    {
        if(end=='\0'||end==str[x].back())
        {
            now_max=len;
            ans_circle.assign(now.begin(),now.end());
        }
    }
    int to=-1;
    for(auto i:g[x])
    {
        if(vis[i]==0&&str[i].front()==str[i].back())
        {
            to=i;
        }
    }
    if(to!=-1)
    {
        now.push_back(str[to]);
        char_len+=str[to].length();
        circle_max(n,to,g,str,op,start,end,ban);
        char_len-=str[to].length();
        now.pop_back();
        vis[x]=0;
        return;
    }
    for(auto i:g[x])
    {
        if(vis[i]==0)
        {
            now.push_back(str[i]);
            char_len+=str[i].length();
            circle_max(n,i,g,str,op,start,end,ban);
            char_len-=str[i].length();
            now.pop_back();
        }
    }
    vis[x]=0;
}
int gen_chain_word(char* words[], int len, char* result[], char head, char tail,char banned,bool enable_loop)
{
    vector<string> all_str;
    for(int i=0;i<len;i++)
        all_str.push_back(words[i]);
    for(int i=0;i<len;i++)
        for(int j=0;j<all_str[i].size();j++)
            if(all_str[i][j]<='Z')
                all_str[i][j]^=32;
    sort(all_str.begin(),all_str.end());
    int sz=unique(all_str.begin(),all_str.end())-all_str.begin();
    all_str.erase(all_str.begin()+sz,all_str.end());
    vector<vector<int> > g=build_graph(all_str);
    set<char> ban;
    if(banned!='\0')
        ban.insert(banned);
    if(enable_loop&&!check(sz,g))
    {
        ans_circle.clear();
        now_max=0;
        now.clear();
        vis=vector<int>(sz,0);
        circle_max(sz,-1,g,all_str,0,head,tail,ban);
        int cnt=0;
        for(auto x:ans_circle)
        {
            result[cnt]=new char[x.size()*sizeof(int)];
            for(int i=0;i<x.size();i++)
                result[cnt][i]=x[i];
            result[cnt][x.size()]='\0';
            cnt++;
        }
        return cnt;
    }
    else
    {
        if(!check(sz,g))
        {
            //cout<<"fucked";
            return -3;
        }
        vector<string> ans=get_max(sz,g,all_str,0,head,tail,ban);
        int cnt=0;
        if(ans.size()==1)
            return 0;
        for(auto x:ans)
        {
            result[cnt]=new char[x.size()*sizeof(int)];
            for(int i=0;i<x.size();i++)
                result[cnt][i]=x[i];
            result[cnt][x.size()]='\0';
            cnt++;
            //cout<<x<<" "<<x.data()<<" "<<result[cnt-1]<<"\n";
        }
        return cnt;
    }
}
int gen_chain_char(char* words[], int len, char* result[],char head, char tail,char banned,bool enable_loop)
{
    vector<string> all_str;
    for(int i=0;i<len;i++)
        all_str.push_back(words[i]);
    for(int i=0;i<len;i++)
        for(int j=0;j<all_str[i].size();j++)
            if(all_str[i][j]<='Z')
                all_str[i][j]^=32;
    sort(all_str.begin(),all_str.end());
    int sz=unique(all_str.begin(),all_str.end())-all_str.begin();
    all_str.erase(all_str.begin()+sz,all_str.end());
    vector<vector<int> > g=build_graph(all_str);
    set<char> ban;
    if(banned!='\0')
        ban.insert(banned);
    if(enable_loop&&!check(sz,g))
    {
        ans_circle.clear();
        now_max=0;
        now.clear();
        vis=vector<int>(sz,0);
        circle_max(sz,-1,g,all_str,1,head,tail,ban);
        int cnt=0;
        for(auto x:ans_circle)
        {
            result[cnt]=new char[x.size()*sizeof(int)];
            for(int i=0;i<x.size();i++)
                result[cnt][i]=x[i];
            result[cnt][x.size()]='\0';
            cnt++;
        }
        return cnt;
    }
    else
    {
        if(!check(sz,g))
        {
            //cout<<"fucked";
            return -3;
        }
        vector<string> ans=get_max(sz,g,all_str,1,head,tail,ban);
        if(ans.size()==1)
            return 0;
        int cnt=0;
        for(auto x:ans)
        {
            result[cnt]=new char[x.size()*sizeof(int)];
            for(int i=0;i<x.size();i++)
                result[cnt][i]=x[i];
            result[cnt][x.size()]='\0';
            cnt++;
            //cout<<result[0]<<"\n";
        }
        return cnt;
    }
}
int gen_chains_all(char* words[], int len, char* result[])
{
    vector<string> all_str;
    for(int i=0;i<len;i++)
        all_str.push_back(words[i]);
    for(int i=0;i<len;i++)
        for(int j=0;j<all_str[i].size();j++)
            if(all_str[i][j]<='Z')
                all_str[i][j]^=32;
    sort(all_str.begin(),all_str.end());
    int sz=unique(all_str.begin(),all_str.end())-all_str.begin();
    all_str.erase(all_str.begin()+sz,all_str.end());
    vector<vector<int> > g=build_graph(all_str);
    if(!check(sz,g))
    {
        //cout<<"fucked";
        return -3;
    }
    all_list.clear();
    get_all(sz,g,all_str,-1);
    int cnt=0;
    if (all_list.size() > 20000) {
        return all_list.size();
    }
    for(auto x:all_list)
    {
        string tmp="";
        for(auto y:x)
            tmp+=y,tmp+=" ";
        result[cnt]=new char[tmp.size()*sizeof(int)];
        for(int i=0;i<tmp.size();i++)
            result[cnt][i]=tmp[i];
        result[cnt][tmp.size()-1]='\0';
        cnt++;
        //for(int i=0;i<cnt;i++) cout<<result[i]<<" ";
    }
    //for(int i=0;i<6;i++) cout<<result[i]<<"\n";
    return cnt;
}
