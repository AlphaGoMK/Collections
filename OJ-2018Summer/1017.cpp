#include<iostream>
#include<cmath>
using namespace std;
int a[24];
char ch;
int main(){
	for(int i=1;i<24;i++){
		a[i]=2*i*i-1;
	}
	a[0]=0;
	int N;
	while(cin>>N>>ch&&!cin.eof()){
		int k=0;
		while(k<24&&a[k]<=N) k++;
		k--;
		for(int i=0;i<k;i++){
			for(int j=0;j<i;j++) cout<<" ";
			for(int j=0;j<2*(k-i)-1;j++) {
				cout<<ch;
			}
			for(int j=0;j<i;j++) cout<<" ";
			cout<<endl;
		}
		for(int i=1;i<k;i++){
			for(int j=0;j<k-i-1;j++) cout<<" ";
			for(int j=0;j<2*i+1;j++) {
				cout<<ch;
			}
			for(int j=0;j<k-i-1;j++) cout<<" ";
			cout<<endl;
		}
		cout<<N-a[k]<<endl;
	}
	return 0;
}
