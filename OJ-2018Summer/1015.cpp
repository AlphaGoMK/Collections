#include<iostream>
#include<vector>
using namespace std;

struct node{
	string addr;
	int data;
	string ne;
	node* next;
};

int print(node* a){
	node* now=a->next;
	while(now!=NULL){
		cout<<now->addr<<" "<<now->data<<" "<<now->ne<<endl;
		now=now->next;
	}
	return 0;
}
int main(){
	node *li;
	int N,K;
	string start;
	while(cin>>start>>N>>K&&!cin.eof()){
		vector<node*> vec;
		for(int i=0;i<N;i++){
			node* tmp=new node;
			cin>>tmp->addr>>tmp->data>>tmp->ne;
			vec.push_back(tmp);
		}
		
		node *head=new node;
		
		string nextaddr=start;
		node *curnode=head;
		N=0;
		while(nextaddr!="-1"){
			for(int i=0;i<vec.size();i++){
				if(vec[i]->addr==nextaddr){
					curnode->next=vec[i];
					break;
				}
			}
			curnode=curnode->next;
			nextaddr=curnode->ne;
			N++;
		}
		curnode->next=NULL;
		if(K<=1){
			print(head);
			continue;
		}
		
		int cnt=0;
		node *now=head->next,*pre=head;
		node *top=pre,*tail,*last;
		while(cnt<N/K){
			for(int i=0;i<K-1;i++){
				int idx=0;
				while(idx<K-i-1){
					pre=now;
					now=now->next;
					idx++;
				}
				if(i==0) {
					tail=now->next;
					last=now;
				}
				now->next=pre;
				now->ne=pre->addr;
				
				pre=top;
				now=pre->next;
			}
			// step
			now=tail;
			pre=top->next;
			// connect
			
			top->next->next=tail;
			if(tail!=NULL)
				top->next->ne=tail->addr;
			else 
				top->next->ne="-1";
			top->next=last;
			top->ne=last->addr;
			// step
			top=pre;
			
			cnt++;
			
		}
		print(head);

	}	
	return 0;
}

// 节点不在链表中
// K=1
// K>N
 
