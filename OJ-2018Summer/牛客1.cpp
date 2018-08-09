#include<iostream>
#include<cstring>
#include<vector>
using namespace std;

int done[257];
vector<int> pos[257];
int main(){
    int count[257];
    string s;
    while(cin>>s&&!cin.eof()){
        memset(count,0,sizeof(count));
        memset(done,0,sizeof(done));
        for(int i=0;i<s.length();i++){
            pos[s[i]+128].push_back(i);
            count[s[i]+128]++;
        }
        
        for(int i=0;i<s.length();i++){
            if(!done[s[i]+128]&&count[s[i]+128]>1){
                for(vector<int>::iterator it=pos[s[i]+128].begin();it!=pos[s[i]+128].end();it++){
                    if(it!=pos[s[i]+128].begin()) cout<<",";
                    cout<<s[i]<<":"<<*it;
                }
                cout<<endl;
            }
        }
    }
    return 0;
}
