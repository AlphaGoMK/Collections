#include<iostream>
using namespace std;
int main(){
	int T,idx=1;
	cin>>T;
	while(T--){
		long long a,b,c;
		bool res=false;
		cin>>a>>b>>c;
		if((a+b>c)||(a>0&&b>0&&a+b<0)){
			if(a<0&&b<0&&a+b>0) {
				cout<<"Case #"<<idx<<": false"<<endl;
			}
			else cout<<"Case #"<<idx<<": true"<<endl;
		}
		else cout<<"Case #"<<idx<<": false"<<endl;
		
		idx++;
	}
	return 0;
} 
