#include<iostream>
using namespace std;
int main(){
	int a0,a1,p,q,k;
	while(cin>>a0>>a1>>p>>q>>k&&!cin.eof()){
		int ap=a1%10000,app=a0%10000;
		long long ak;
		for(int i=2;i<=k;i++){
			ak=(p*(ap%10000)+q*(app%10000))%10000;
			app=ap;
			ap=ak;
		}
		cout<<ak<<endl;
	}
}
