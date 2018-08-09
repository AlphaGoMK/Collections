#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;
int school[100001];
int main(){
	int N;
	while(cin>>N&&!cin.eof()){
		memset(school,0,sizeof(school));
		while(N--){
			int sch,score;
			cin>>sch>>score;
			school[sch]+=score;
		}
		int max=0,idx=0;
		for(int i=0;i<100001;i++){
			if(school[i]>max){
				max=school[i];
				idx=i;
			}
		}
		cout<<idx<<" "<<max<<endl;
	}
	return 0;
}
