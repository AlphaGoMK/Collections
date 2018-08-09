#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

int pow(int base,int time){
	int res=1;
	while(time--){
		res*=base;
	}
	return res;
}
int main(){
	int n;
	while(cin>>n&&!cin.eof()){
		int visit[1010],tmp;
		memset(visit,0,sizeof(visit));
		for(int i=0;i<n;i++){
			cin>>visit[i];	// 输入为编号而不是位置，所以输出为某些位置对应的元素值即可 
		}
		int level,flag=0;
		cin>>level;
		for(int i=pow(2,level-1);i<pow(2,level)&&i<n;i++){	// 保证不越界 
			if(flag!=0) cout<<" "; 
			cout<<visit[i-1];
			flag=1;	
		}
		if(!flag) cout<<"EMPTY";
		cout<<endl;
	}
	return 0;
}
