#include<iostream>
using namespace std;
int main(){
	long long a,b;
	int d;
	while(cin>>a>>b>>d&&!cin.eof()){
		unsigned long long s=a+b;
		string res="";
		if(s==0) res="0";
		else{
			while(s!=0){
				res+=(s%d+'0');
				s/=d;
			}			
		}
		for(int i=res.length()-1;i>=0;i--){
			cout<<res[i];
		}
		cout<<endl;
	}
	return 0;
}
