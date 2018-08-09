#include<iostream>
#include<cstdio>
#include<cstring>
#include<deque>
using namespace std;

string rot(string s, int idx){
	string ret=s;
	ret[idx]=s[idx+1];
	ret[idx+1]=s[idx];
	return ret;
}

bool match(string s){
	for(int i=0;i<s.length()-3;i++){
		if(s[i]=='2'&&s[i+1]=='0'&&s[i+2]=='1'&&s[i+3]=='2') {
			return true;
		}
	}
	return false;
}

int main(){
	int N;
	string s;
	while(scanf("%d",&N)!=EOF){
		int res=0,got=0;
		deque<string> que;
		cin>>s;
		que.push_back(s);
		for(int i=0;i<N*(N-1)/2;i++){
			
			for(int j=0;j<que.size();j++){
				if(match(que[j])) got=1;
			}
			
			if(got==1) break;
			res++;
			
			int len=que.size();
			for(int j=0;j<len;j++){
				string tmp=que.front();
				for(int k=0;k<N-1;k++){
					string tmp2=rot(tmp,k);
					que.push_back(tmp2);
				}
				que.pop_front();
			}
			
		}
		if(got==0) printf("%d\n",-1);
		else printf("%d\n",res);
	}
	return 0;
}
