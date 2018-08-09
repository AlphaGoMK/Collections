#include<iostream>
#include<cstring>
using namespace std;
int res[10000];

int main(){
	
	int N;
	while(cin>>N&&!cin.eof()){
		if(N==0) {
			cout<<1<<endl;
			continue;
		}
		memset(res,0,sizeof(res));
		int len=1;	// 初始长度为1 
		res[0]=1;	// 最低位为1，不然一直为0 
		for(int i=1;i<=N;i++){
			int over=0;
			for(int j=0;j<len;j++){	//  每次乘积，超过10化为10以内数和进位over 可能不止一位（>10） 
				res[j]=res[j]*i+over;
				over=res[j]/10;		// 之前的多位进位不需要处理，全部累加留到最后一位再去处理 
				res[j]=res[j]%10;
			}
			while(over>0){	// 进位全部累加到最后一位，然后再去处理长度变化 
				res[len]=over%10;
				over/=10;
				len++;
			}
		}
		
		for(int i=len-1;i>=0;i--){
			cout<<res[i];
		}
		cout<<endl;
	}
}
