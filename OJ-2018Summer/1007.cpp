#include<cstdio>
#include<cstring>
using namespace std;
int main(){
	char a[1000],res[1000];
	int b;
	while(scanf("%s",a)!=EOF){
		scanf("%d",&b);
		int idx=0,tmp=0;
		for(int i=0;i<strlen(a);i++){
			tmp=tmp*10+(a[i]-'0');
			res[idx++]=tmp/b+'0';
			tmp=tmp%b;
		}
		res[idx]='\0';
		int j=0;
		while(j<strlen(res)&&res[j]=='0') j++;
		if(j==strlen(res)) printf("0");	// deal with Q=0
		else{
			for(;j<strlen(res);j++){
				printf("%c",res[j]);
			}	
		}

		printf(" %d\n",tmp);
		memset(a,0,sizeof(a));
		memset(res,0,sizeof(res));
	}
} 
