#include<iostream>
using namespace std;

int pin[12]={31,28,31,30,31,30,31,31,30,31,30,31};
int run[12]={31,29,31,30,31,30,31,31,30,31,30,31};
int main(){
	int Y,M,D;
	while(scanf("%d%d%d",&Y,&M,&D)!=EOF){
		int isrun=0,res=0;
		if((Y%100!=0&&Y%4==0)||(Y%400==0)) isrun=1;
		if(isrun){
			for(int i=0;i<M-1;i++){
				res+=run[i];
			}
			res+=D;
		}
		else {
			for(int i=0;i<M-1;i++){
				res+=pin[i];
			}
			res+=D;
		}
		
		printf("%d\n",res);
	}
	return 0;
}
