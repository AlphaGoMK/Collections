#include<iostream>
#include<string>
#include<cstring>
using namespace std;
struct money{
	long long g,s,k;
};
unsigned long long trans(money a){
	return (a.g*17+a.s)*29+a.k;
}
int print(unsigned long long a){
	cout<<a/(17*29)<<".";
	a%=(17*29);
	cout<<a/29<<".";
	a%=29;
	cout<<a<<endl;
	return 0;
}
int main(){
	money a,b;
	string s1,s2;
	cin>>s1>>s2;
	long long idx1=-1,idx2=-1;
	for(int i=0;i<s1.length();i++){
		if(s1[i]=='.'&&idx1==-1) idx1=i;
		else if(s1[i]=='.') idx2=i;
	}
	a.g=stoll(s1.substr(0,idx1));
	a.s=stoll(s1.substr(idx1+1,idx2-idx1-1));
	a.k=stoll(s1.substr(idx2+1,s1.length()-idx2-1));
	idx1=idx2=-1;
	for(int i=0;i<s2.length();i++){
		if(s2[i]=='.'&&idx1==-1) idx1=i;
		else if(s2[i]=='.') idx2=i;
	}
	b.g=stoll(s2.substr(0,idx1));
	b.s=stoll(s2.substr(idx1+1,idx2-idx1-1));
	b.k=stoll(s2.substr(idx2+1,s2.length()-idx2-1));
	long long res=trans(b)-trans(a);
	if(res<0) {
		res*=-1;
		cout<<"-";
	}
	print(res);
	return 0;
} 
