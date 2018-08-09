#include<iostream>
#include<vector>
using namespace std;
// 0-1-2 5-4-3
int a[3];
vector<string> res;
void dfs(int n, string s){
	if(n==3){
		if(a[0]*100+a[1]*10+a[2]+a[2]+a[2]*10+a[1]*100==532){
			res.push_back(s);
			return;
		}
	}
	else{
		if(n==2){
			s+=(6+'0');
			a[2]=6;
			dfs(3,s);
			
			s=s.substr(0,s.length()-1);
			s+=(1+'0');
			a[2]=1;
			dfs(3,s);
		}
		else{
			for(int i=0;i<10;i++){
				s+=(i+'0');
				a[n]=i;
				dfs(n+1,s);
				s=s.substr(0,s.length()-1);	// delete last
			}
		}
	}
}
int main(){
	string s="";
	dfs(0,s);
	for(int i=0;i<res.size();i++){
		string ans=res[i];
		if(ans[0]=='0'||ans[1]=='0') continue;	// distinguish letter and number
		cout<<ans[0]<<" "<<ans[1]<<" "<<ans[2]<<endl;
	}
	return 0;
}
