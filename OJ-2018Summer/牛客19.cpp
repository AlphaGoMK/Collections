#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std; 
// 分情况递归，抓住关键，2的幂次中唯一一个奇数1
//可以用递推，对于一个整数n，分为奇数和偶数，我们应该分情况讨论。 
// 1.如果为奇数，那么在这个表示中一定含有一个1，把这个1减去，就是n-1 
// 即dp[n]=dp[n-1]。 
// 2.如果为偶数，那么也分两种情况，有1和没1。对于有1的情况可以直接拆出两个1，然后变为n-2的情况。对于没有1的情况可以直接将其转化为n/2，因为n拆分出所有的数字都是2的倍数，只需要将每种拆分结果中的数字都除以2就会与n/2的一种拆分相对应。 
unsigned long long dp[1000010];
int main(){
	memset(dp,0,sizeof(dp));
	
	dp[1]=1;
	dp[2]=2;
	
	long long N;
	while(scanf("%ld",&N)!=EOF){
		for(int i=3;i<=N;i++){
			if(i%2==0){
				dp[i]=(dp[i/2]%1000000000+dp[i-1]%1000000000)%1000000000;	// 没有1，直接除2减半；有1，拆成1和i-1.而i-1按照奇数处理。拆出单独的1 
			}
			else dp[i]=dp[i-1];
		}
		printf("%ld",dp[N]);
	}
	return 0;
}
