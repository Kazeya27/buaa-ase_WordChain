#include<bits/stdc++.h>
using namespace std;
ifstream readFile;
// diao yong dll
// shengming hanshu
ofstream fout("output.txt");
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
void print_ans(vector<string> ans)
{
	if(ans.size()<=1)
	{
		fout<<"no word chain\n";
		return;
	}
	fout<<ans.size()<<"\n";
	for(auto s:ans)
		fout<<s<<"\n";
}
void print_all()
{
	if(all_list.size()<=1)
	{
		fout<<"no word chain\n";
		return;
	}
	fout<<all_list.size()<<"\n";
	for(auto x:all_list)
	{
		for(auto y:x)
		{
			fout<<y<<" ";
		}
		fout<<"\n";
	}
}
int main(int argc,char* argv[])
{
	if(argc<2)
	{
		cout<<"too few para!";
		return -2;
	}
	readFile.open(argv[argc-1], ios::in);
	if(!readFile.is_open())
	{
		cout<<"open file failed!";
		return -3;
	}
	vector<string> all_str=input();
	sort(all_str.begin(),all_str.end());
	int sz=unique(all_str.begin(),all_str.end())-all_str.begin();
	//print_ans(all_str);
	vector<vector<int> > g=build_graph(all_str);
	//char* word[10]={"aec","cef","fb","bdfsdfrrd","dear"};
	//char* result[10];
	//gen_chain_word_char(word,5,result,'0','0','0',0);
	//test
	char start='0',end='0',b[100]={'b'};
	int op=-1,loop=0,qall=0;
	set<char> ban;
	//string cmd[10]={"-w","-c","-h","-t","-j","-r","-n"};
	for(int i=1;i<argc-1;i++)
	{
		string ag=argv[i];
		if(ag=="-w") 
		{
			if(op!=-1) 
			{
				cout<<"wrong para!";
				return -3;
			}
			op=0;
		}
		else if(ag=="-c") 
		{
			if(op!=-1) 
			{
				cout<<"wrong para!";
				return -3;
			}
			op=1;
		}
		else if(ag=="-h") 
		{
			i++;
			start=argv[i][0];
		}
		else if(ag=="-t")
		{
			i++;
			end=argv[i][0];
		}
		else if(ag=="-j")
		{
			i++;
			ban.insert(argv[i][0]);
		}
		else if(ag=="-r") 
		{
			loop=1;
		}
		else if(ag=="-n") 
		{
			qall=1;
		}
		else
		{
			cout<<"wrong para!";
			return -3;
		}
	}
	if(qall==1)
	{
		init(sz);
		get_all(sz,g,all_str,-1);
		print_all();
		return 0;
	}
	if(loop==0)
	{
		if(!check(sz,g))
		{
			cout<<"fucked";
			return -1;
		}	
		vector<string> ans=get_max(sz,g,all_str,op,start,end,ban);
		print_ans(ans);
		return 0;
	}
	else
	{
		init(sz);
		circle_max(sz,-1,g,all_str,op,start,end,ban);
		print_ans(ans_circle);
		return 0;
	}
	//test
	/*
	
	
	cout<<"#####\n";
	vector<string> ans=get_max(sz,g,all_str,0,start,end,ban);
	print_ans(ans);
	cout<<"#####\n";
	ans=get_max(sz,g,all_str,1,start,end,ban);
	print_ans(ans);
	*/
	
}
