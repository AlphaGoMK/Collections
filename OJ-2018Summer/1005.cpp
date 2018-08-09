#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct stu{
	string id;
	int de;
	int cai;
};
bool cmp(stu a,stu b){
	if(a.de+a.cai==b.de+b.cai){
		if(a.de==b.de){
			return a.id<b.id;
		}
		return a.de>b.de;
	}
	return a.de+a.cai>b.de+b.cai;
}

vector<stu> vec1,vec2,vec3,vec4;
int main(){
	int N,L,H;
	while(cin>>N>>L>>H&&!cin.eof()){
		for(int i=0;i<N;i++){
			stu tmp;
			cin>>tmp.id>>tmp.de>>tmp.cai;
			if(tmp.de<L||tmp.cai<L) continue;
			else if(tmp.de>=H&&tmp.cai>=H) vec1.push_back(tmp);
			else if(tmp.de>=H) vec2.push_back(tmp);
			else if(tmp.de>=tmp.cai) vec3.push_back(tmp);
			else vec4.push_back(tmp);
		}
		sort(vec1.begin(),vec1.end(),cmp);
		sort(vec2.begin(),vec2.end(),cmp);
		sort(vec3.begin(),vec3.end(),cmp);
		sort(vec4.begin(),vec4.end(),cmp);
		cout<<vec1.size()+vec2.size()+vec3.size()+vec4.size()<<endl;
		for(int i=0;i<vec1.size();i++){
			cout<<vec1[i].id<<" "<<vec1[i].de<<" "<<vec1[i].cai<<endl;
		}
		for(int i=0;i<vec2.size();i++){
			cout<<vec2[i].id<<" "<<vec2[i].de<<" "<<vec2[i].cai<<endl;
		}
		for(int i=0;i<vec3.size();i++){
			cout<<vec3[i].id<<" "<<vec3[i].de<<" "<<vec3[i].cai<<endl;
		}	
		for(int i=0;i<vec4.size();i++){
			cout<<vec4[i].id<<" "<<vec4[i].de<<" "<<vec4[i].cai<<endl;
		}
		vec1.clear(),vec2.clear(),vec3.clear(),vec4.clear();
	}
	return 0;
}

/*
test case:
14 60 80
101 59 61
102 99 99
103 99 59
104 59 99
105 90 90
106 79 99
107 99 79
108 79 79
109 79 79
110 75 79
111 79 75
112 92 88
113 88 92
114 100 100
*/
