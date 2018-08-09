#include<iostream>
using namespace std;

struct node{
	int k;
	node* l;
	node* r;
};

int main(){
	int N;
	while(cin>>N&&!cin.eof()){
		node *t,*fa,*now;
		t=NULL,fa=NULL,now=NULL;
		while(N--){
			int tmp;
			cin>>tmp;
			if(t==NULL){
				t=new node;
				t->k=tmp;
				t->l=t->r=NULL;
				cout<<-1<<endl;
			}
			else {
				now=t;
				while(now!=NULL) {	// 记得初始化为NULL才能使用now!=NULL判断，否则为任意值 
					if(tmp<now->k) {
						fa=now;
						now=now->l;
					}
					else {
						fa=now;
						now=now->r;
					}
				}
				now=new node;
				now->k=tmp;
				now->l=now->r=NULL;
				if(tmp>fa->k){
					fa->r=now;
				}
				else fa->l=now;
				
				cout<<fa->k<<endl;
			}
			
		}
	}
	return 0;
}
