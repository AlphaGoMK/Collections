#include<iostream>
#include<cstring>
using namespace std;
int broken[256];
int occur[256];
char u2l(char a){
	if(a>='a'&&a<='z') return a-'a'+'A';
	else return a;
}
int main(){
	string s1,s2;
	while(cin>>s1>>s2&&!cin.eof()){
		memset(occur,0,sizeof(occur));
		memset(broken,0,sizeof(broken));
		for(int i=0;i<s2.length();i++){
			occur[u2l(s2[i])]=1;
		}
		for(int i=0;i<s1.length();i++){
			if(occur[u2l(s1[i])]==0) {
				if(broken[u2l(s1[i])]==0){
					broken[u2l(s1[i])]=1;
					cout<<u2l(s1[i]);
				}
			}
		}
		
		cout<<endl;
		
	}
	return 0;
}
