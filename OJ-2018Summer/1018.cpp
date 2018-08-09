#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;
struct info{
	string name;
	string date;
};
int bigger(info i1,info i2){
	string s1=i1.date,s2=i2.date;
	int y1=stoi(s1.substr(0,4)),y2=stoi(s2.substr(0,4)),m1=stoi(s1.substr(5,2)),m2=stoi(s2.substr(5,2)),d1=stoi(s1.substr(8,2)),d2=stoi(s2.substr(8,2));
	if(y1!=y2) return y1-y2;
	if(m1!=m2) return m1-m2;
	else return d1-d2;
}
bool cmp(info i1,info i2){
	return i1.date>i2.date;
}

int main(){
	int N;
	while(cin>>N&&!cin.eof()){
		vector<info> vec;
		info oldbound,youngbound;
		oldbound.date="1814/09/06";
		youngbound.date="2014/09/06";
		int cnt=0;
		for(int i=0;i<N;i++){
			info tmp;
			cin>>tmp.name>>tmp.date;
			if(bigger(tmp,youngbound)>0||bigger(tmp,oldbound)<0) continue;
			vec.push_back(tmp);
			cnt++;
		}
		sort(vec.begin(),vec.end(),cmp);
		//for(int i=0;i<vec.size();i++) cout<<vec[i].name<<" ";
		cout<<cnt<<" "<<vec.back().name<<" "<<vec.front().name<<endl;
	}
}
