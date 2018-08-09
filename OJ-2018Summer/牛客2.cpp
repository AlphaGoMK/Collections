#include<iostream>
#include<string>	// 不要同时使用cstring和string
#include<algorithm>
#include<vector>
using namespace std;

// https://blog.csdn.net/lionel_d/article/details/41746135
// sort用大于小于
// qsort用减号
// vector只能用sort不能用qsort
struct rec{
    string name;
    int score;
    int idx;
};

vector<rec> table;
int cmp(rec a, rec b){
	if(a.score==b.score)
		return a.idx<b.idx;
	else return a.score<b.score;
}
int cmp2(rec a, rec b){
	if(a.score==b.score)
		return a.idx<b.idx;
	else return a.score>b.score;
}

int main(){
	
    int n,flag;
    while(cin>>n>>flag&&!cin.eof()){
        table.clear();
        for(int i=0;i<n;i++){
        	rec temp;
    	    cin>>temp.name;
			cin>>temp.score;
    	    temp.idx=i;
    	    table.push_back(temp);
        }
        if(flag==1) sort(table.begin(),table.end(),cmp);	
        else sort(table.begin(),table.end(),cmp2);
    
        for(int i=0;i<n;i++){
        	cout<<table[i].name<<" "<<table[i].score<<endl;
	    }
    }

	return 0;
}
