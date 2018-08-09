#include<iostream>
using namespace std;
int main(){
	int n;
	int a[110][110];
	while(cin>>n&&!cin.eof()){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				cin>>a[i][j];
			}
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				cout<<a[j][i]<<" ";
			}
			cout<<endl;
		}
		
	}
	return 0;
}
