// https://blog.csdn.net/merlini_/article/details/50651349
#include<iostream>
using namespace std;
long long root(long long N,int k){
	long long res=0;
	if(N>=k){
		while(N!=0){
			int remain=N%k;
			res+=remain;
			N=(N-remain)/k;
		}
		return root(res,k);
	}
	else return N;
}

unsigned long long rootk(long long x,long long y,int k){
	if(y==1) return root(x,k);
	if(y%2==0){
		unsigned long long ret=rootk(x,y/2,k);
		return root(ret*ret,k);
	}
	else {
		unsigned long long ret=rootk(x,(y-1)/2,k);
		return root(ret*ret*root(x,k),k);
	}
}

int main(){
	unsigned long long x,y,k;
	while(scanf("%lld%lld%lld",&x,&y,&k)!=EOF){
		printf("%lld\n",rootk(x,y,k));
	}
	return 0;
}
