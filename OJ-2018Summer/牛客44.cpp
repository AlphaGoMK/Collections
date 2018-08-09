#include<iostream>
#include<vector>
using namespace std;

vector<int> t[1000];
int calc(){
	t[0].push_back(1),t[0].push_back(1);
	for(int i=1;i<1000;i++){
		t[i].push_back(1);
		for(int j=0;j<t[i-1].size()-1;j++){
			t[i].push_back(t[i-1].at(j)+t[i-1].at(j+1));
		}
		t[i].push_back(1);
	}
	return 0;
}
int main(){
	int n;
	calc();
	while(cin>>n&&!cin.eof()){
		for(int i=0;i<n-1;i++){
			int flag=0;
			for(int j=0;j<t[i].size();j++) {
				if(flag==0) {
					cout<<t[i].at(j);
					flag=1;
				}
				else {
					cout<<" "<<t[i].at(j);
				}
			}
			cout<<endl;
		}
	}
	return 0;
}
