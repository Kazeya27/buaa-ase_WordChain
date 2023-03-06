#include<bits/stdc++.h>
using namespace std;
int isletter(char c)
{
	return (c>='a'&&c<='z')||(c>='A'&&c<='Z');
}
vector<string> input()
{
	vector<string> res;
	while(1)
	{
		char s[1010];
		string now;
		cin.getline(s,1000);
		if(s[0]=='*') break;
		//use * to end input(test)
		//remember to delete it!
		int len=strlen(s);
		for(int i=0;i<len;i++)
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
vector<vector<int> > build_graph(vector<string> str)
{
	sort(str.begin(),str.end());
	int n=unique(str.begin(),str.end())-str.begin();
	vector<vector<int> > g(n,vector<int>());
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(i==j) continue;
			if(str[i].back()==str[j].front()) 
			{
				g[i].push_back(j);
			}
		}
	}
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
		dp[i]=(op==1?str[i].size():1);
		if(start!='0'&&str[i][0]!=start) dp[i]=-inf;
		if(ban.find(str[i][0])!=ban.end()) dp[i]=-inf;
	}
	for(int i=0;i<n;i++)
		if(rd[i]==0)
			q.push(i);
	while(!q.empty())
	{
		int now=q.front();
		q.pop();
		for(auto i:g[now])
		{
			if(!dp[i]<dp[now]+(op==1?str[i].size():1))
			{
				dp[i]=dp[now]+(op==1?str[i].size():1);
				pre[i]=now;
			}
			rd[i]--;
			if(rd[i]==0) q.push(i);
		}
	}
	//for(int i=0;i<n;i++) cout<<dp[i]<<" ";
	//cout<<endl;
	int pos,mx=0;
	for(int i=0;i<n;i++)
		if(dp[i]>mx&&(end=='0'||str[i].back()==end))
			mx=dp[i],pos=i;
	//cout<<mx<<" "<<pos<<"\n";
	vector<string> res;
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
			if(rd[i]==0) q.push(i);
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
	if(now.size()>1) all_list.push_back(now);
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
			if(start!='0'&&start!=str[i][0]) continue;
			now.push_back(str[i]);
			char_len+=str[i].length();
			circle_max(n,i,g,str,op,start,end,ban);
			char_len-=str[i].length();
			now.pop_back();
		}
		return;
	}
	if(vis[x]==1) return;
	if(ban.find(str[x][0])!=ban.end()) return;
	vis[x]=1;
	int len=(op==0)?now.size():char_len;
	if(len>max(now_max,1)) 
	{
		if(end=='0'||end==str[x].back())
		{
			now_max=len;
			ans_circle.assign(now.begin(),now.end());
		}
	}
	for(auto i:g[x])
	{
		now.push_back(str[i]);
		char_len+=str[i].length();
		circle_max(n,i,g,str,op,start,end,ban);
		char_len-=str[i].length();
		now.pop_back();
	}
	vis[x]=0;
}
int gen_chain_word(char* words[], int len, char* result[],int type, char head, char tail,char banned,bool enable_loop)
{
	vector<string> all_str;
	for(int i=0;i<len;i++) all_str.push_back(words[i]);
	vector<vector<int> > g=build_graph(all_str);
	int sz=all_str.size();
	set<char> ban;
	if(banned!='0') ban.insert(banned);
	if(enable_loop)
	{
		ans_circle.clear();
		now_max=0;
		now.clear();
		vis=vector<int>(sz,0);
		circle_max(sz,-1,g,all_str,type,head,tail,ban);
		int cnt=0;
		for(auto x:ans_circle)
		{
			result[cnt++]=(char *)x.data();
		}
		return 0;
	}
	else
	{
		if(!check(sz,g))
		{
			cout<<"fucked";
			return -1;
		}
		vector<string> ans=get_max(sz,g,all_str,type,head,tail,ban);
		int cnt=0;
		for(auto x:ans)
		{
			result[cnt++]=(char *)x.data();
		}
		return 0;
	}
}
int gen_chains_all(char* words[], int len, char* result[])
{
	vector<string> all_str;
	for(int i=0;i<len;i++) all_str.push_back(words[i]);
	vector<vector<int> > g=build_graph(all_str);
	int sz=all_str.size();
	if(!check(sz,g))
	{
		cout<<"fucked";
		return -1;
	}
	all_list.clear();
	get_all(sz,g,all_str,-1);
	int cnt=0;
	for(auto x:all_list)
	{
		string tmp="";
		for(auto y:x) tmp+=y,tmp+=" ";
		result[cnt++]=(char *)tmp.data();
		cout<<"\n";
	}
	return 0;
}
void print_ans(vector<string> ans)
{
	cout<<ans.size()<<"\n";
	for(auto s:ans)
		cout<<s<<"\n";
}
void print_all()
{
	cout<<all_list.size()<<"\n";
	for(auto x:all_list)
	{
		for(auto y:x)
		{
			cout<<y<<" ";
		}
		cout<<"\n";
	}
}
int main(int argc,char* argv[])
{
	vector<string> all_str=input();
	int sz=all_str.size();
	vector<vector<int> > g=build_graph(all_str);
	
	
	//test
	char start='0',end='0',b[100]={'b'};
	int op=0;
	set<char> ban;
	for(int i=1;i<argc;i++)
	{
		if(argv[i]=="-w") op=0;
		else if(argv[i]=="-c") op=1;
		else if(argv[i]=="-h") 
		{
			i++;
			start=argv[i][0];
		}
		else if(argv[i]=="-t")
		{
			i++;
			end=argv[i][0];
		}
		else if(argv[i]=="-j")
		{
			i++;
			ban.insert(argv[i][0]);
		}
	}
	vis=vector<int>(sz,0);
	circle_max(sz,-1,g,all_str,op,start,end,ban);
	//vector<string> ans=get_max(sz,g,all_str,op,start,end,ban);
	print_ans(ans_circle);
	//test
	/*
	if(!check(sz,g))
	{
		cout<<"fucked";
		return 0;
	}
	get_all(sz,g,all_str,-1);
	print_all();
	cout<<"#####\n";
	vector<string> ans=get_max(sz,g,all_str,0,start,end,ban);
	print_ans(ans);
	cout<<"#####\n";
	ans=get_max(sz,g,all_str,1,start,end,ban);
	print_ans(ans);
	*/
	
}
