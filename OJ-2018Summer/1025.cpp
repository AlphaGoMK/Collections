/*
插入排序是将每个输入立即插入到一个有序序列中，实时排序，从长度为1，到n到n+1的有序序列，依次扩展长度，来一个排一个，中间前半部分有序后半部分无序 ，这个依据判断是否为插入排序 
归并排序是每k个排序，最后余量再单独排序，然后k*=2，最后到k>n停止 
只要模拟排序过程，知道排序过程中序列和b序列相等，在进行一次排序 就是结果 
*/
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
bool cmp(int a,int b){
	return a<b;
}
int main(){
	int N;
	while(cin>>N&&!cin.eof()){
		int a[101],b[101];
		for(int i=0;i<N;i++) cin>>a[i];
		for(int i=0;i<N;i++) cin>>b[i];
		int ordlen=1;
		for(int i=0;i<N-1;i++){
			if(b[i]<=b[i+1]) ordlen++;
			else break;
		}
		
		int flag=0;
		for(int i=ordlen;i<N;i++) {
			if(a[i]!=b[i]) {
				flag=1;
				break;
			}
		}
		
		if(flag==0) cout<<"Insertion Sort"<<endl;
		else cout<<"Merge Sort"<<endl;
		
		if(flag==0){
			sort(a,a+ordlen+1,cmp);
		}
		else{
			
			int ok=0,len=2;
			while(!ok){
				ok=1;
				for(int i=0;i<N;i++){
					if(a[i]!=b[i]) ok=0;
				}
				
				// one more time
				for(int i=0;i<N/len;i++){
					sort(a+i*len,a+(i+1)*len,cmp);
				}
				sort(a+N-N%len,a+N,cmp);	
				len*=2;
			}
			
			
		}
		
		
		for(int i=0;i<N;i++) cout<<a[i]<<" ";
		cout<<endl;
	}
}


