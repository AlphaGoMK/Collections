#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
vector<unsigned long long> vec;
int bsearch(int l,int r,unsigned long long key){
	int mid=(l+r)/2;
	if(r-l==1||r==l) return l;
	if(vec[mid]<=key){
		return bsearch(mid,r,key);
	}
	else return bsearch(l,mid,key);
}
int main(){
	int N,P;
	while(cin>>N>>P&&!cin.eof()){
		for(int i=0;i<N;i++) {
			unsigned long long tmp;
			cin>>tmp;
			vec.push_back(tmp);
		}
		
		sort(vec.begin(),vec.end());
		
		int maxnum=0,tmpnum=0;
		for(int i=0;i<vec.size();i++){
			if(P*vec[i]>=vec.back()) tmpnum=vec.size()-i;
			else {
				int idx=bsearch(i,vec.size()-1,P*vec[i]);
				tmpnum=idx-i+1;
			}
			
			if(tmpnum>maxnum) maxnum=tmpnum;
		}
		cout<<maxnum<<endl;
		vec.clear();
	}
	return 0;
}

