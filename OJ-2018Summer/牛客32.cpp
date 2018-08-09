#include<iostream>
#include<cstring>
#include<deque>
#include<queue>
using namespace std;
int weight[1005];
int n;
struct node{
	int n;
	node *l,*r;
};
bool operator > (node a,node b){
	return a.n>b.n;
}

priority_queue<node,vector<node>, greater<node> > tree;	// 默认大项堆，使用小项堆的时候需要使用greater，同时重载大于号 
int solve(){
	int sum=0;
	for(int i=0;i<n;i++){
		node tmp;
		tmp.n=weight[i];
		tmp.l=tmp.r=NULL;
		tree.push(tmp);
	}
	while(tree.size()>1){
		
		node a=tree.top();
		tree.pop();
		node b=tree.top();
		tree.pop();
		node c;
		c.l=&a;
		c.r=&b;
		c.n=a.n+b.n;
		sum+=c.n;	// 每次求出两个点的和的时候加到sum中，计算路径长度 
		tree.push(c);
	}
	return sum;
}
int main(){
	while(cin>>n&&!cin.eof()){
		for(int i=0;i<n;i++){
			cin>>weight[i];
		}
		cout<<solve()<<endl;
	}
}
