#include<iostream>
#include<algorithm>
using namespace std;

int main(){
	string s;
	while(cin>>s&&!cin.eof()){
		sort(s.begin(),s.end());
		do{
			cout<<s<<endl;
		}while(next_permutation(s.begin(),s.end()));	
		cout<<endl;	
	}
	return 0;
}
