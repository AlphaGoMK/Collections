#include<iostream>
#include<cmath>
using namespace std;

int solve(long long a){
	long long num=0;
	long long half=sqrt(a);
	for(int i=1;i<=half;i++){
		if(a%i==0) num+=2;
	}
	if(half*half==a) num--;
	
	return num;
}
int main(){
	int N;
	while(scanf("%d",&N)!=EOF&&N!=0){
		long long a;
		while(N--){
			scanf("%ld",&a);
			printf("%ld\n",solve(a));
		}
	}
	return 0;
} 
