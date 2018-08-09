#include<iostream>
#include<vector>
#include<deque>
using namespace std;

vector<int>res;
deque<int>digit;
int solve(){
	res.clear();
	while(!digit.empty()){
		if(digit[digit.size()-1]%2==1){
			digit[digit.size()-1]--;
			res.push_back(1);
		}
		else{
			res.push_back(0);
		}
		
		for(int i=0;i<digit.size();i++){
			int mod=digit[i]%2;
			digit[i]/=2;
			if(i!=digit.size()-1)digit[i+1]+=mod*10;
		}
		if(digit[0]==0) digit.pop_front();		
	}
	
	return 0;
	
}
int main(){
	string s;
	while(cin>>s&&!cin.eof()){
		digit.clear();
		for(int i=0;i<s.length();i++){
			digit.push_back((s[i]-'0'));
		}
		solve();
		for(int i=res.size()-1;i>=0;i--){
			cout<<res[i];
		}
		cout<<endl;
	}
	return 0;
}
