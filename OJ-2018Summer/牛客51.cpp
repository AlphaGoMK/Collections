#include<iostream>
using namespace std;
int main(){
	int n;
	while(cin>>n&&!cin.eof()){
		int max=-1e7,min=1e7,x,maxidx,minidx;
		int a[30],idx=0;
		while(n--){
			cin>>x;
			if(x>max) {
				max=x;
				maxidx=idx;
			}
			if(x<min){
				min=x;
				minidx=idx;
			}
			a[idx++]=x;
		}
		int tmp=a[maxidx];
		a[maxidx]=a[minidx];
		a[minidx]=tmp;
		for(int i=0;i<idx;i++) cout<<a[i]<<" ";
		cout<<endl;
	}
	return 0;
}
