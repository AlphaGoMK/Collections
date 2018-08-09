#include<iostream>
#include<vector>
using namespace std;
struct frac{
	int flag;
	int up;
	int down;
};
int gcd(int a,int b){
	if(a<b){
		int tmp=a;
		a=b;
		b=tmp;
	}
	if(b==0) return a;
	return gcd(b,a%b);
}

string simplify(frac f){
	string res="";
	int up=f.up,down=f.down,flag=f.flag;
	int g=gcd(up,down);
	up/=g,down/=g;
	if(flag==-1&&up!=0) res+="-";
	if(up==0){
		res+="0";
	}
	else if(down==1) {
		res+=to_string(up);
	}
	else if(up>down){
		res+=to_string(up/down);
		res+=" ";
		res+=(to_string(up%down)+"/"+to_string(down));
	}
	else if(up<down){
		res+=(to_string(up)+"/"+to_string(down));
	}
	
	return res;
} 

frac str2frac(string s){
	string upper="",lower="";
	int idx=0,flag=1;
	int up=0,down=0;
	for(int i=0;i<s.length();i++){
		if(s[i]=='/'){
			idx=i;
			break;
		}
	}
	if(s[0]=='-') {
		flag=-1;
		up=stoi(s.substr(1,idx-1));
	}
	else up=stoi(s.substr(0,idx));
	down=stoi(s.substr(idx+1,s.length()-idx-1));
	
	frac res;
	res.flag=flag;
	res.up=up;
	res.down=down;
	return res;
}

frac add(frac f1,frac f2){
	
}
int main(){
	//cout<<simplify("6/3")<<" "<<simplify("-5/3")<<" "<<simplify("0/6")<<endl;
	
	string s1,s2;
	while(cin>>s1>>s2&&!cin.eof()){
		frac f1=str2frac(s1),f2=str2frac(s2);
		
	}
	return 0;
}
