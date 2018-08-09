#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;
int main(){
	double x0,y0,z0,x1,y1,z1;
	while(cin>>x0>>y0>>z0>>x1>>y1>>z1&&!cin.eof()){
		double rad=sqrt((x0-x1)*(x0-x1)+(y0-y1)*(y0-y1)+(z0-z1)*(z0-z1));
		double v=acos(-1)*rad*rad*rad*4/3;
		cout<<fixed<<setprecision(3)<<rad<<" "<<v<<endl;
	}
	return 0;
}
