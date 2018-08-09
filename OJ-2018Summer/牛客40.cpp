#include<iostream>
#include<cstring>
using namespace std;
string reverse(string s){
	string res="";
	for(int i=0;i<s.length();i++) res+=s[s.length()-1-i];
	return res;
}
string merge(string s1,string s2){
	string res="";
	for(int i=0;i<s1.length();i++){
		res+=s1[i];
		res+=s2[i];
	}
	return res;
}
int main(){
	string s1,s2;
	while(cin>>s1>>s2&&!cin.eof()){
		s2=reverse(s2);
		cout<<merge(s1,s2)<<endl;
	}
	return 0;
}
