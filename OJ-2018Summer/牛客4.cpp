#include<iostream>

using namespace std;

unsigned long long fact(int x){
	unsigned long long ans=1;
	for(int i=1;i<=x;i++){
		ans*=i;
	}
	return ans;
}
int main(){
	int n;
	unsigned long long a[10],b[10];
	unsigned long long cnt=0;
	for(int i=0;i<5;i++){
		cnt+=fact(2*i+1);
		a[i]=cnt;
	}
	cnt=0;
	for(int i=0;i<5;i++){
		cnt+=fact(2*i+2);
		b[i]=cnt;
	}
	while(cin>>n&&!cin.eof()){
		if(n%2==0){
			cout<<a[n/2-1]<<" "<<b[n/2-1]<<endl;
		}
		else{
			cout<<a[n/2]<<" "<<b[n/2-1]<<endl;
		}
	}
	
	return 0;
}
