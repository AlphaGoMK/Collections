#include<iostream>
using namespace std;
int gcd(int a, int b){
	while(b>0){
		int c=a%b;
		a=b;
		b=c;
	}
	return a;
}
int main(){
	int n;
	while(cin>>n&&!cin.eof()){
		int a[610];
		for(int i=0;i<n;i++){
			cin>>a[i];
		}
		
		int cnt=0;
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(a[i]!=a[j]&&gcd(a[i],a[j])==1){
					cnt++;
				}
			}
		}
		cnt/=2;
		
		cout<<cnt<<endl;
	}
	return 0;
} 
