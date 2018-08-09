#include<iostream>
#include<algorithm>
#include<vector>
#include<iomanip>
using namespace std;

struct cake{
	double amount;
	double price;
	double div;
};

bool cmp(cake a,cake b){
	return a.div>b.div;
}

int main(){
	int N,D;
	while(cin>>N>>D&&!cin.eof()){
		vector<cake> vec;
		for(int i=0;i<N;i++) {
			cake tmp;
			cin>>tmp.amount;
			vec.push_back(tmp);
		}
		for(int i=0;i<vec.size();i++){
			cin>>vec.at(i).price;
			vec.at(i).div=vec[i].price/vec[i].amount;
		}
		sort(vec.begin(),vec.end(),cmp);
		
		double cur=D;
		int idx=0;
		double profit=0;
		while(cur>0){
			if(vec[idx].amount<=cur){
				cur-=vec[idx].amount;
				profit+=vec[idx].price;
				idx++;
			}
			else {
				profit+=(cur*vec[idx].div);
				cur=0;
			}
		}
		
		cout<<fixed<<setprecision(2)<<profit<<endl;	// fixed << setprecision(2)
		
	}
	return 0;
}
