#include<iostream>
using namespace std;
int main(){
	string s1,s2,s3,s4;
	cin>>s1>>s2>>s3>>s4;
	int d,h,m,cnt=0;
	for(int i=0;i<s1.length();i++){
		if(s1[i]==s2[i]&&s1[i]>='A'&&s1[i]<='Z'){
			if(s1[i]>='A'&&s1[i]<='Z')
				d=s1[i]-'A'+1;
			else d=s1[i]-'a'+1;
			cnt=i;
			break;
		}
	}
	for(int i=cnt+1;i<s1.length();i++){
		if(s1[i]==s2[i]){
			if(s1[i]>='0'&&s1[i]<='9'){
				h=s1[i]-'0';
			} 
			else h=s1[i]-'A'+10;
			break;
		}
	}
	for(int i=0;i<s3.length();i++){
		if(s3[i]==s4[i]&&((s3[i]>='a'&&s3[i]<='z')||(s3[i]>='A'&&s3[i]<='Z'))) {
			m=i;
			break;
		}
	}

	switch(d){
		case 1:
			cout<<"MON";
			break;
		case 2:
			cout<<"TUE";
			break;
		case 3:
			cout<<"WED";
			break;
		case 4:
			cout<<"THU";
			break;
		case 5:
			cout<<"FRI";
			break;
		case 6:
			cout<<"SAT";
			break;
		case 7:
			cout<<"SUN";
			break;
		default:
			break;
	}
	printf(" %02d:%02d\n",h,m);	// %02d Ìî³ä³ÉÁ½Î» 
	return 0;
	
}
