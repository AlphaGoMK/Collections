#include<iostream>
using namespace std;
char match[11]={'1','0','X','9','8','7','6','5','4','3','2'};
int w[17]={7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2};
int main(){
	int N;
	while(cin>>N&&!cin.eof()){
		string s;
		int flag=0;
		while(N--){
			cin>>s;
			long long res=0;
			for(int i=0;i<17;i++){
				res+=(s[i]-'0')*w[i];
			}
			//cout<<res<<endl;
			res%=11;
			//cout<<match[res]<<endl;
			if(match[res]!=s[17]){
				flag=1;
				cout<<s<<endl;
			}	
		}

		if(flag==0) cout<<"All passed"<<endl;
	}
	return 0;
} 
