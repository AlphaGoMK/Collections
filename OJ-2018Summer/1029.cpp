#include<iostream>
#include<cstring>
using namespace std;
int main(){
	string s1,pattern;
	cin>>s1>>pattern;
	int contain[256],need[256];
	memset(contain,0,sizeof(contain));
	memset(need,0,sizeof(need));
	for(int i=0;i<s1.length();i++){
		contain[s1[i]]++;
	}
	for(int i=0;i<pattern.length();i++){
		need[pattern[i]]++;
	}
	int lack=0,lacknum=0,exceednum=0;
	for(int i=0;i<256;i++){
		if(contain[i]<need[i]) lack=1;
		if(contain[i]>=need[i]){
			exceednum+=(contain[i]-need[i]);
		}
		else {
			lack=1;
			lacknum+=(need[i]-contain[i]);
		}
	}
	if(lack){
		cout<<"No "<<lacknum<<endl;
	}
	else cout<<"Yes "<<exceednum<<endl;
}
