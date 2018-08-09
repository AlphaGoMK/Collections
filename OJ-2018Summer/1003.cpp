#include<iostream>
#include<cstring>
using namespace std;
int odd[1000100];
int main(){
	int count=0;
	memset(odd,0,sizeof(odd));
	for(int i=2;i<=1000;i++){
		int fac=2;
		while(fac*i<1000100){
			odd[fac*i]=1;
			fac++;
		}
	}
	odd[0]=1;
	odd[1]=1;
	int m,n;
	while(cin>>m>>n&&!cin.eof()){
		int cnt=0,output=0;
		for(int i=0;i<1000100;i++){
			if(odd[i]==0) {
				cnt++;	
				if(cnt>=m) {
					cout<<i;
					output++;

					
					if(cnt>=n) {
						cout<<endl;
						break;
					}
					else {
						if(output%10==0) cout<<endl;	// 内部输出，防止多次输出 
						else cout<<" ";
					}
					// 已经输出了几个 
				}

			}
		}
	}
	return 0;
}
