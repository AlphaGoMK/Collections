#include<iostream>
#include<cmath>
using namespace std;
int main(){
	int N;
	char c;
	while(cin>>N>>c&&!cin.eof()){
		for(int i=0;i<N;i++) cout<<c;
		cout<<endl;
		int height=round(N/2.0);
		for(int i=0;i<height-2;i++){
			cout<<c;
			for(int j=0;j<N-2;j++) cout<<" ";
			cout<<c<<endl;
		}
		for(int i=0;i<N;i++) cout<<c;
		cout<<endl;
	}
	return 0;
} 
