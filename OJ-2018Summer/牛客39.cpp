#include<iostream>
#include<cstring>
#include<vector>
#include<cstdlib>
using namespace std;

int swaprow(int a[][11], int i, int j, int n){
	int tmp=0;
	for(int k=0;k<n;k++){
		tmp=a[i][k];
		a[i][k]=a[j][k];
		a[j][k]=tmp;
	}
	return 0;
}
int solve(int a[][11],int n){	// 数组参数第二维必须指定  
	for(int i=0;i<n-1;i++){
		int maxrow=i;
		for(int j=i;j<n;j++){
			if(a[j][i]>a[maxrow][i]) maxrow=j;
		}
		//cout<<i<<" "<<maxrow<<endl;
		swaprow(a,i,maxrow,n);
	}
	return 0;
}
int main(){
	int N;
	while(cin>>N&&!cin.eof()){
		int a[11][11];
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				cin>>a[i][j];
			}
		}
		solve(a,N);
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				cout<<a[i][j]<<" ";
			}
			cout<<endl;
		}
	}
	return 0;
}
