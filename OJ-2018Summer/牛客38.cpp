#include<iostream>
#include<cstring>
#include<vector>
#include<cstdlib>
using namespace std;

struct comp{
	int a;
	int b;
};
int main(){
	int n;
	while(cin>>n&&!cin.eof()){
		vector<comp> li;
		while(n--){
			string s="";
			char x=getchar();
			getline(cin,s);	// getline函数读入空格 ， 但会错误读入回车
			if(x!='\n') s=x+s;
			//cout<<s<<" OK"<<endl;
			if(s.substr(0,3)=="Pop"){
				int idx,max=-1;
				for(int i=0;i<li.size();i++){
					if(li[i].a*li[i].a+li[i].b*li[i].b>max) {
						max=li[i].a*li[i].a+li[i].b*li[i].b;
						idx=i;	
					}
				}
				if(max==-1) cout<<"empty"<<endl;
				else {
					string res="";
					char str[20];
					//sprintf(str, "%d", li[idx].a); 	// itoa is not decleared in Linux OS, use sprintf instead
					itoa(li[idx].a,str,10);
					for(int i=0;i<strlen(str);i++){
						res+=str[i];
					}
					if(li[idx].b<0){
						res+="-i";
						memset(str,0,sizeof(str));
						itoa(-1*li[idx].b,str,10);
						for(int i=0;i<strlen(str);i++){
							res+=str[i];
						}
					}
					else if(li[idx].b>0){
						res+="+i";
						memset(str,0,sizeof(str));
						itoa(li[idx].b,str,10);
						for(int i=0;i<strlen(str);i++){
							res+=str[i];
						}						
					}
					else {
						res+="+i0";
					}
					cout<<res<<endl;
					
					int t=0;
					for(vector<comp>::iterator it=li.begin();it!=li.end();it++){
						if(t==idx){
							li.erase(it);
							break;
						}
						t++;
					}
					cout<<"SIZE = "<<li.size()<<endl;
				}
				
			}
			else if(s.substr(0,6)=="Insert"){
				s=s.substr(7,s.length()-7);
				//cout<<s<<endl;
				string re,im;
				int pos=-1;
				for(int i=0;i<s.length();i++){
					if(s[i]=='i') {
						pos=i;
						break;
					}
				}
				re=s.substr(0,pos-1);
				im=s[pos-1]+s.substr(pos+1,s.length()-pos-1);
				//cout<<re<<" + "<<im<<endl;
				comp temp;
				temp.a=atoi(re.c_str());
				temp.b=atoi(im.c_str());
				li.push_back(temp);
				cout<<"SIZE = "<<li.size()<<endl;
			}
		}
		
		
	}
	return 0;
}
