#include<iostream>
#include<cstring>
#include<vector>
#include<cmath>
using namespace std;
int prime[60];

int solve(int a){
	vector<int> li;
	for(int i=1;i<=sqrt(a);i++){
		if(a%i==0){
			if(i==1){
				li.push_back(1);
			}
			else if(i*i==a){
				li.push_back(i);
			}
			else {
				li.push_back(i);
				li.push_back(a/i);
			}
		}
	}
	int sum=0;
	for(int i=0;i<li.size();i++){
		sum+=li[i];
	}
	return a-sum;
}
int main(){
	vector<int> E;
	vector<int> G;
	for(int i=2;i<=60;i++){
		if(solve(i)==0) E.push_back(i);
		else if(solve(i)<0) G.push_back(i);
	}
	
	cout<<"E:";
	for(int i=0;i<E.size();i++){
		cout<<" "<<E[i];
	}
	cout<<"\nG:";
	for(int i=0;i<G.size();i++){
		cout<<" "<<G[i];
	}
	return 0;
} 
