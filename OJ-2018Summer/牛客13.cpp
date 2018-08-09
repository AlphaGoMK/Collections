#include<iostream>
using namespace std;

unsigned long long place(int m,int n){
	if(n==1||m==0){
		return 1;	// 不可能0个盘子
					// 放到1个盘子或者0个苹果
					// 最后使用m-n，最终情况为m-n=0，所以不需要考虑苹果数为1的情况 
	}
	if(m<n)
		return place(m,m);	// 苹果数少于盘数，一定有至少n-m个盘子空，所以不需要考虑这些盘子
	else return place(m,n-1)+place(m-n,n); 
}
int main(){
	int n,m;
	while(cin>>m>>n&&!cin.eof()){
		cout<<place(m,n)<<endl;
	}
	return 0;
} 
