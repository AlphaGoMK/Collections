#include<iostream>
using namespace std;
int main(){
	int a,d1,b,d2;
	long long res1=0,res2=0;
	while(cin>>a>>d1>>b>>d2&&!cin.eof()){
		while(a!=0){
			if(a%10==d1){
				res1=res1*10+d1;
			}
			a=a/10;
		}
		while(b!=0){
			if(b%10==d2){
				res2=res2*10+d2;
			}
			b=b/10;
		}
		cout<<res1+res2<<endl;
	}
	return 0;
}
