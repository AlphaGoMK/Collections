#include<iostream>
#include<cstring>
using namespace std;

void Swap(char *a, char *b){
	char temp=*a;
	*a=*b;
	*b=temp;
} 

void allrange(char *str, int start, int length){
	if(start==length-1){
		printf("%s\n",str);
	}
	else {
		for(int i=start;i<length;i++){
			Swap(&str[start],&str[i]);
			allrange(str,start+1,length);
			Swap(&str[start],&str[i]);	// 从下标start数开始与后面的开始交换，在进入下一级交换。结束后再交换恢复 
		}
	}
}
// 输出按顺序，从00换到01换到02换。即从不换开始，到b开始，到c开始（从后开始向前换，最后两个换，最后三个换etc） 
int main(){
	char a[10];
	cin>>a;
	allrange(a,0,strlen(a));
	return 0;
}
