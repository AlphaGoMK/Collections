#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

char getNext(char a){
	char res;
	
	if(!((a>='a'&&a<='z')||(a>='A'&&a<='Z'))) return a;
	res=a+1;
	if(a=='z'||a=='Z'){
		res-=26;
	}
	return res;
} 

int main(){
	char a[100];
	
	gets(a);
	for(int i=0;i<100;i++){
		if(a[i]=='\0') break;
		else {
			printf("%c",getNext(a[i]));
		}
	}
	printf("\n");
	memset(a,0,sizeof(a));

	
	return 0;
}
