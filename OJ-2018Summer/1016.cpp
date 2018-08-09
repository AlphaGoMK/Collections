#include<iostream>
#include<cmath>
#include<string>
using namespace std;
string sec2hms(int n){
	string res="";
	if(n/3600<10&&n/3600>0) res+="0";
	if(n/3600>0) res+=(to_string(n/3600)+":");
	else res+="00:";
	n%=3600;
	if(n/60>0&&n/60<10) res+="0";
	if(n/60>0) res+=(to_string(n/60)+":");
	else res+="00:";
	n%=60;
	if(n>0&&n<10) res+="0";
	if(n>0) res+=(to_string(n));
	else res+="00";
	return res;
}
int main(){
	int c1,c2;
	while(cin>>c1>>c2&&!cin.eof()){
		int sec=round((c2-c1)/100.0);	// ËÄÉáÎåÈë	, divided by 100.0 to get float result, NOT 100
		//cout<<sec<<endl; 
		cout<<sec2hms(sec)<<endl;
	}
	return 0;
} 
