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
vector<vector<int> > build_graph(int n,vector<string> str)
{
	set<string> st;//unique
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
vector<string> get_max(int n,vector<vector<int> > g,vector<string> str,int op)
//op==0 : max word cnt,op==1 : max character cnt
{
	vector<int> rd(n,0),dp(n,0),pre(n,-1);
	queue<int> q;
	for(int i=0;i<n;i++)
	{
		for(auto j:g[i])
			rd[j]++;
		dp[i]=(op==1?str[i].size():1);
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
			if(dp[i]<dp[now]+(op==1?str[i].size():1))
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
		if(dp[i]>mx)
			mx=dp[i],pos=i;
	cout<<mx<<" "<<pos<<"\n";
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
vector<string> now;
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
int main()
{
	vector<string> all_str=input();
	int sz=all_str.size();
	vector<vector<int> > g=build_graph(sz,all_str);
	if(!check(sz,g))
	{
		cout<<"fucked";
		return 0;
	}
	get_all(sz,g,all_str,-1);
	print_all();
	cout<<"#####\n";
	vector<string> ans=get_max(sz,g,all_str,0);
	print_ans(ans);
	cout<<"#####\n";
	ans=get_max(sz,g,all_str,1);
	print_ans(ans);
	
	
}
