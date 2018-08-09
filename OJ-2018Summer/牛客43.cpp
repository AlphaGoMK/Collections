#include<iostream>
#include<cstring>
using namespace std;

int main(){
	string s="";
	char a[1000];
	gets(a);
	for(int i=0;i<strlen(a);i++) s+=a[i];
	cout<<s<<endl;
	int cnt=0;
	int flag=0;
	for(int i=0;i<s.length();i++){
		if(s[i]==' '&&flag==0) cnt=0;
		else if((s[i]==' '||s[i]=='.')&&flag==1){
			cout<<cnt;
			if(s[i]!='.') cout<<" ";
			flag=0;
			cnt=0;
		}
		else {
			cnt++;
			flag=1;
		}
	}
	cout<<endl;
	return 0;
}
