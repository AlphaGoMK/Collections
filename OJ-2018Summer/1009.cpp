#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

bool cmp(char a,char b){
	return a>b;
}
int myitoa(int num,char * arr){
	arr[4]='\0';
	arr[3]=num%10+'0';
	num/=10;
	
	arr[2]=num%10+'0';
	num/=10;
	arr[1]=num%10+'0';
	num/=10;
	arr[0]=num%10+'0';
	return 0;
}
int main(){
	char a[5];
	memset(a,0,sizeof(a));
	int x;
	while(scanf("%d",&x)!=EOF){
		myitoa(x,a);
		do{
			sort(a,a+strlen(a),cmp);
			if(a[0]==a[3]) {
				printf("%s - %s = 0000\n",a,a);
				break;
			}
			printf("%s - ",a);
			int op1=atoi(a);
			sort(a,a+strlen(a));
			printf("%s = ",a);
			int op2=atoi(a);
			myitoa(abs(op1-op2),a);
			printf("%s\n",a);			
		}while(atoi(a)!=6174);
		memset(a,0,sizeof(a));
	}	
	return 0;
}
