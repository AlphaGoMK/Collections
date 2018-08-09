#include<iostream>
using namespace std;

struct Info{
	int id;
	string name;
	string sex;
	int age;
};
int main(){
	int n;
	while(cin>>n&&!cin.eof()){
		Info stu[1010];
		for(int i=0;i<n;i++){
			cin>>stu[i].id>>stu[i].name>>stu[i].sex>>stu[i].age;
		}
		int m;
		cin>>m;
		for(int i=0;i<m;i++){
			int idx;
			cin>>idx;
			int flag=0;
			for(int j=0;j<n;j++){
				if(stu[j].id==idx){
					cout<<stu[j].id<<" "<<stu[j].name<<" "<<stu[j].sex<<" "<<stu[j].age<<endl;
					flag=1;
					break;
				}
			}
			if(flag==0) cout<<"No Answer!"<<endl;
		}
	}
	return 0;
}
