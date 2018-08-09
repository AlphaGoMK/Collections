#include<iostream>
#include<cstring>
#include<vector>
using namespace std;

int base[15][15];
int factor(int a[15][15],int n,int m){
	int tmp[15][15];
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			tmp[i][j]=a[i][j];
		}
	}
	int flag=m%2;
	if(m==1) return 0;
	if(m%2==1) m-=1;
	while(m!=0){
		if(m==1) break;
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				int res=0;
				for(int k=0;k<n;k++){
					res+=a[i][k]*a[k][j];
				}
				tmp[i][j]=res;
			}
		}
		m/=2;
		
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				a[i][j]=tmp[i][j];
			}
		}
	}
	
	if(flag){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				int res=0;
				for(int k=0;k<n;k++){
					res+=a[i][k]*base[k][j];
				}
				tmp[i][j]=res;
			}
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				a[i][j]=tmp[i][j];
			}
		}	
	}
	
	return 0;
}

int main(){
	int n,m;
	while(cin>>n>>m&&!cin.eof()){
		int a[15][15];
		memset(base,0,sizeof(a));
		
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				cin>>a[i][j];
				base[i][j]=a[i][j];
			}
		}
		factor(a,n,m);
		
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				cout<<a[i][j]<<" ";
			}
			cout<<endl;
		}		
	}
}
