#include<iostream>
using namespace std;
int main(){
	long long n;
	while(cin>>n&&!cin.eof()){
		long long dp=0,x,global=-0x7fffffffffffffff;
		cin>>x;
		dp=x;
		global=dp;
		for(int i=1;i<n;i++){
			cin>>x;
			if(x>dp+x) dp=x;	// dp 表示以n结尾的最大序列和，一定包含n，局部最优；在使用global记录最大全局最大的序列和 
			else dp=dp+x;
			
			if(dp>global) global=dp;
		}
		cout<<global<<endl;
	}
	return 0;
}
