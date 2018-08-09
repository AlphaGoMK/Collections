#include<iostream>
using namespace std;

struct Pair{
	int x;
	int y;
};

bool operator < (Pair &a, Pair &b){
	if(a.x==b.x) return a.y<b.y;
	else return a.x<b.x;
}

int main(){
	int n;
	Pair a[1005];
	while(cin>>n&&!cin.eof()){
		for(int i=0;i<n;i++) cin>>a[i].x>>a[i].y;
		Pair min;
		min.x=10000000;
		min.y=min.x;
		for(int i=0;i<n;i++){
			if(a[i]<min) min=a[i];
		}
		cout<<min.x<<" "<<min.y<<endl;
	}
	return 0;
} 
