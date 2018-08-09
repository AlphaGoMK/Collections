#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int main(){
	int m,n,x,ans=0;
	priority_queue<int> li;
	cin>>m>>n;
	while(n--){
		cin>>x;
		li.push(x);
	}
	while(m>0&&!li.empty()){
		int cand=li.top();
		if(cand>m) {
			li.pop();
		}
		else{
			m-=cand;
			li.pop();
			ans++;
		}
	}
	if(m!=0) cout<<"0"<<endl;
	else cout<<ans<<endl;
	return 0;
}
