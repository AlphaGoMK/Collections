#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

int surpass(int a[],int b[],int n,int m){
	if(m==1){
		for(int i=0;i<n;i++) {
			if(a[i]>b[0]) return 1;
		}
		return 0;
	}
	else if(m==2){
		for(int i=0;i<n-1;i++){
			if(a[i]>b[0]&&a[i]==a[i+1]) return 1;
		}
		return 0;
	}
	else if(m==3){
		for(int i=0;i<n-2;i++){
			if(a[i]>b[0]&&a[i]==a[i+1]&&a[i+1]==a[i+2]) return 1;
		}
		return 0;		
	}
	else if(m==5){
		int visit[10];
		memset(visit,0,sizeof(visit));
		for(int i=0;i<n;i++){
			visit[a[i]]=1;
		}
		for(int i=b[0]+1;i<6;i++){
			if(visit[i]==1&&visit[i+1]==1&&visit[i+2]==1&&visit[i+3]==1&&visit[i+4]==1) return 1;
		}
		return 0;		
	}
	return 0;
}

int main(){
	string s1,s2;
	while(cin>>s1>>s2&&!cin.eof()){
		int a[110],b[110];
		for(int i=0;i<s1.length();i++){
			a[i]=s1[i]-'0';
		}
		for(int i=0;i<s2.length();i++){
			b[i]=s2[i]-'0';
		}
		if(surpass(a,b,s1.length(),s2.length())==0) cout<<"NO"<<endl;
		else cout<<"YES"<<endl;
	}
	return 0;
}
