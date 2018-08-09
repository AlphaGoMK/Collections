#include<iostream>
#include<vector>
using namespace std;
int main(){
	int a[10];
	while(cin>>a[0]&&!cin.eof()){
		for(int i=1;i<10;i++) cin>>a[i];
		
		string res="";
		int idx=1;
		while(idx<10&&a[idx]==0) idx++;
		if(idx==10) {
			cout<<"0"<<endl;
			continue;	
		}
		else {
			res+=(idx+'0');
			a[idx]--;	
		}
		int flag=0;
		while(true){
			idx=0;
			while(idx<10&&a[idx]==0) idx++;
			if(idx==10){
				break;
			}
			else {
				res+=(idx+'0');
				a[idx]--;
			}
		}
		cout<<res<<endl;
		for(int i=0;i<10;i++) a[i]=0;
	}
	return 0;
}
