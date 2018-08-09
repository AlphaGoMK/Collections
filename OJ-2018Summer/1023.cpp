#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

int broken[256];

int main(){
	string badkey;
	string input;
	while(cin>>badkey>>input&&!cin.eof()){
		memset(broken,0,sizeof(broken));
		for(int i=0;i<badkey.length();i++) {
			broken[badkey[i]]=1;
			if(badkey[i]>='A'&&badkey[i]<='Z') broken[badkey[i]-'A'+'a']=1;	
		}
		if(broken['+']==1){
			for(int i='A';i<='Z';i++) broken[i]=1;
		}
		
		for(int i=0;i<input.length();i++){
			if(broken[input[i]]==0) cout<<input[i]; 
		}
		cout<<endl;
	}
	return 0;
}
