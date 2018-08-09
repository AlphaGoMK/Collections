#include<iostream>
#include<cstring>
using namespace std;

long long a[2010],b[2010];

int main(){
	int n;
	int coe,time;
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	cin>>n;
	while(n--){
		cin>>coe>>time;
		a[time+1000]=coe;
	}
	cin>>n;
	while(n--){
		cin>>coe>>time;
		b[time+1000]=coe;
	}
	
	int flag=0;
	for(int i=2005;i>=0;i--){
		
		if(a[i]+b[i]!=0) {
			if(flag==0){
				flag=1;
			}
			else {
				cout<<" ";
			}
			cout<<a[i]+b[i]<<" "<<i-1000;
		}
	}
	cout<<endl;

	return 0;
}
