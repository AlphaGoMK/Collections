#include<iostream>
#include<cstring>
#include<vector>
#include<iomanip>
using namespace std;

int a[1010];
vector<int> a1;
vector<int> a2;
vector<int> a4;
int main(){
	int N;
	cin>>N;
	long long res1=0,res2=0,res3=0,res5=-0x7fffffffffffffff;
	double res4=0.0;
	memset(a,0,sizeof(a));
	for(int i=0;i<N;i++){
		cin>>a[i];
		if(a[i]%10==0){
			a1.push_back(a[i]);
		}
		else if(a[i]%5==1){
			a2.push_back(a[i]);
		}
		else if(a[i]%5==2){
			res3++;
		}
		else if(a[i]%5==3){
			a4.push_back(a[i]);
		}
		else if(a[i]%5==4){
			if(a[i]>res5) res5=a[i];
		}
	}
	
	int flag=1;
	for(int i=0;i<a2.size();i++){
		res2+=(flag*a2[i]);
		flag*=-1;
	}
	for(int i=0;i<a1.size();i++){
		res1+=a1[i];
	}
	for(int i=0;i<a4.size();i++){
		res4+=a4[i];
	}
	if(!a4.empty()) res4/=a4.size();
	
	if(a1.empty()) cout<<"N ";
	else cout<<res1<<" ";
	if(a2.empty()) cout<<"N ";
	else cout<<res2<<" ";
	if(res3==0) cout<<"N ";
	else cout<<res3<<" ";
	if(a4.empty())  cout<<"N ";
	else cout<<fixed<<setprecision(1)<<res4<<" ";
	if(res5==-0x7fffffffffffffff) cout<<"N";
	else cout<<res5;
	return 0;
}
