#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
int main(){
	string s;
	while(cin>>s&&!cin.eof()){
		int n;
		cin>>n;
		while(n--){
			int start,len;
			string op;
			cin>>op;
			start=op[1]-'0',len=op[2]-'0';
			if(op[0]=='0'&&len!=1){
				
				string rev="";
				for(int i=0;i<len;i++){
					rev+=s[start+len-1-i];
				}
				for(int i=start;i<start+len;i++){
					s[i]=rev[i-start];
				}
				//cout<<rev<<endl;
			}
			else if(op[0]=='1'){
				string tail=s.substr(start+len,s.length()-start-len);
				string subs=op.substr(3,op.length()-3);
				for(int i=start;i<start+subs.length();i++){
					s[i]=subs[i-start];
				}
				s=s.substr(0,start+subs.length());
				//cout<<s<<endl;
				s+=tail;
			}
			cout<<s<<endl;
		}
		
	}
	return 0;
}
