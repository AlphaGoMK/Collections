#include<iostream>
using namespace std;
struct node{
	node* l;
	node* r;
	char c;
};
string s;
int visit[110];
node* firstorder(int idx){
	if(idx>=s.length()) return NULL;
	visit[idx]=1;
	if(s[idx]=='#'){
		return NULL;
	}
	else {
		node* tmp=new node;
		tmp->c=s[idx];
		tmp->l=firstorder(idx+1);
		int i=0;
		for(i=idx+1;i<s.length();i++){
			if(visit[i]==0) break;
		}
		tmp->r=firstorder(i);
		return tmp;
	}
}

void outputmidorder(node* t){
	if(t==NULL) return;
	outputmidorder(t->l);
	cout<<t->c<<" ";
	outputmidorder(t->r);
	return;
}

int main(){
	while(cin>>s&&!cin.eof()){
		for(int i=0;i<110;i++){
			visit[i]=0;
		}
		
		node *T;
		T=firstorder(0);
		
		outputmidorder(T);
	}
	return 0;
}
