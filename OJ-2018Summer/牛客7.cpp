#include<iostream>
#include<vector>
#include<cstdio>
#include<cstring>
using namespace std;

char dict[8][4]={{'a','b','c','0'},{'d','e','f','0'},{'g','h','i','0'},{'j','k','l','0'},{'m','n','o','0'},{'p','q','r','s'},{'t','u','v','0'},{'w','x','y','z'}};
bool isDelay(char a,char b){
	int ia=-1;
	int ib=-1;
	for(int i=0;i<8;i++){
		for(int j=0;j<4;j++){
			if(dict[i][j]==a){
				ia=i;
			}
			if(dict[i][j]==b){
				ib=i;
			}
			
		}
		if(ia==ib&&ia!=-1) return true;
	}
	return false;
}

int getTime(char a){
	for(int i=0;i<8;i++){
		for(int j=0;j<4;j++){
			if(dict[i][j]==a){
				return j+1;
			}
		}
	}
}

int main(){
	char a[110];
	int len=0,ans=0;
	while(scanf("%s",a)!=EOF){	// scanf return EOF at end of input 
		len=strlen(a);
		for(int i=0;i<len-1;i++){
			ans+=getTime(a[i]);
			if(isDelay(a[i],a[i+1])) ans+=2;
			
		}
		ans+=getTime(a[len-1]);
		cout<<ans<<endl;
		
		memset(a,0,sizeof(a));
		ans=0;
	}
	return 0;
}
