#include<iostream>
#include<vector>
using namespace std;

int main(){
	long long n;
	while(cin>>n&&!cin.eof()){
		vector<int> tok; 
		while(n!=0){
			tok.push_back(n%8);
			n/=8;
		}
		for(int i=tok.size()-1;i>=0;i--)
			cout<<tok[i];
		cout<<endl;
	}
	return 0;
}
