#include<cstdio>
#include<cstring>
using namespace std;
int notprime[10010];

int main(){
	memset(notprime,0,sizeof(notprime));
	for(int i=2;i<=100;i++){
		for(int j=2;i*j<=10000;j++){
			notprime[i*j]=1;
		}
	}
	
	int n;
	while(scanf("%d",&n)!=EOF){
		int flag=0;
		for(int i=2;i<n;i++){
			if(notprime[i]==0&&i%10==1&&flag==1) printf(" %d",i);
			else if(notprime[i]==0&&i%10==1&&flag==0) {
				printf("%d",i);
				flag=1;	
			}
		}
		if(flag==0) printf("%d",-1);
		printf("\n");
	}
	return 0;
}
