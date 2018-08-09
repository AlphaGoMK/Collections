#include<iostream>
#include<cstring>
#include<stack>
using namespace std;

int road[10010];
stack<int> s;
int main(){
	int l,m;
	while(cin>>l>>m&&!cin.eof()){
		int cnt=0;
		memset(road,0,sizeof(road));
		while(!s.empty()) s.pop();
		int be,en;
		for(int i=0;i<m;i++){
			cin>>be>>en;
			road[be]+=1;
			road[en]-=1;
		}
		
		for(int i=0;i<=l;i++){
			if(road[i]>0){
				for(int j=0;j<road[i];j++) s.push(i);
			}
			else if(road[i]<0){
				for(int j=0;j<-road[i];j++){
					int start=s.top();
					s.pop();
					if(s.empty()) cnt+=(i-start+1);
				}
			}
		}
		
		cout<<l+1-cnt<<endl;
	}
}
