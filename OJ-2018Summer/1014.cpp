#include<iostream>
#include<cstring>
#include<vector>
using namespace std;

int main(){
	string s;
	while(cin>>s&&!cin.eof()){
		
		int flag1=0,flag2=0;
		for(int i=0;i<s.length();i++){
			if(s[i]=='+'||s[i]=='-'){
				if(flag1==0) {
					if(s[i]=='+') flag1=1;
					else flag1=-1;
				}
				else {
					if(s[i]=='+') flag2=1;
					else flag2=-1;
				}
			}
		}
		
		int flag=0;
		vector<char> pre,post;
		for(int i=0;i<s.length();i++){
			if(s[i]=='E') flag=1;
			else if(s[i]>='0'&&s[i]<='9'){
				if(flag==0) pre.push_back(s[i]);
				else post.push_back(s[i]);
			}
		}
		
		int level=0;
		for(int i=0;i<post.size();i++){
			level*=10;
			level+=(post[i]-'0');
		}
		
		string res="";
		res+=(flag1==1?"":"-");
		if(level==0){
			res+=pre[0];
			res+=".";
			for(int i=1;i<pre.size();i++) res+=pre[i];
		}
		else{
			if(flag2==1){
				res+=pre[0];
				int cnt=0;
				for(int i=1;i<pre.size();i++){
					res+=pre[i];
					cnt++;
					if(cnt==level&&i!=pre.size()-1) res+=".";
				}
				while(cnt<level) {
					res+="0";
					cnt++;
				}
			}
			else {
				res+="0.";
				for(int i=1;i<level;i++) res+="0";
				for(int i=0;i<pre.size();i++) res+=pre[i];
			}			
		}

		cout<<res<<endl;
	}
	return 0;
}
