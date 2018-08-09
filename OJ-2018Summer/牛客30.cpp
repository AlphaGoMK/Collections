#include<iostream>
#include<cstring>
using namespace std;

string pattern;
char chset[1000];
int idx=0;
string pre,post;

bool chmatch(char a,char b){
	if(a>='A'&&a<='Z') a=a-'A'+'a';
	if(b>='A'&&b<='Z') b=b-'A'+'a';
	if(a==b) return true;
	else return false;
}

bool isin(char a){
	for(int i=0;i<idx;i++){
		if(chmatch(chset[i],a)) return true;
	}
	return false;
}
int solvepattern(){
	int tok=0,flag=0;
	idx=0;
	pre="";
	post="";
	memset(chset,0,sizeof(chset));
	while(tok<pattern.length()){
		if(pattern[tok]=='['){
			flag=1;
			tok++;
			while(pattern[tok]!=']') {
				chset[idx++]=pattern[tok];
				tok++;
			}
			tok++;
			continue;
		}
		else if(flag==0){
			pre+=pattern[tok];
			tok++;
		}
		else if(flag==1){
			post+=pattern[tok];
			tok++;
		}
	}
	
	return 0;
}
bool match(string s){
	int flag=0;	// is in pattern match
	int tok=0,pos=-1;
	int i=0,j=0;
	
	if(s.length()<pre.length()+post.length()) return false;
	while(i<pre.length()){
		if(chmatch(s[i],pre[i])) i++;
		else return false;
	}
	while(j<post.length()){
		if(chmatch(s[s.length()-1-j],post[post.length()-1-j])) j++;
		else return false;
	}
	
	if(i+j==s.length()){
		if(idx==0) return true;
		else return false;
	}
	

	
	for(int tok=i;tok<=s.length()-1-j;tok++){
		if(!isin(s[tok])) return false;
		flag=1;
	}
	
	return true;
	
}
int main(){
	int N;
	string s[1005];
	while(scanf("%d",&N)!=EOF){
		for(int i=0;i<N;i++){
			cin>>s[i];
		}
		cin>>pattern;
		solvepattern();
		for(int  i=0;i<N;i++){
			if(match(s[i])) {
				cout<<i+1<<" "<<s[i]<<endl;
			}
		}

	}
	return 0;
} 
