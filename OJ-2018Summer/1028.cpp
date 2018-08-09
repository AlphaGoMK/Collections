#include<iostream>
using namespace std;
int main(){
	int N;
	int a[101];
	for(int i=0;i<101;i++) a[i]=0;
	int sc;
	cin>>N;
	while(N--) {
		cin>>sc;
		a[sc]++;
	}
	
	int k;
	cin>>k;
	while(k--) {
		cin>>sc;
		cout<<a[sc];
		if(k!=0) cout<<" ";
	}
	return 0;
}

