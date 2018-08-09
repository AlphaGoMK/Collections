#include<iostream>
using namespace std;
int main(){
	string s;
	while(cin>>s&&!cin.eof()){
		int a[10];
		for(int i=0;i<10;i++) a[i]=0;
		for(int i=0;i<s.length();i++) a[s[i]-'0']++;
		
		for(int i=0;i<10;i++){
			if(a[i]>0) cout<<i<<":"<<a[i]<<endl;
		}
		
	}
	return 0;
}
