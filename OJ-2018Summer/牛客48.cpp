#include<iostream>
#include<vector>
using namespace std;

int a[700][700];	// part1
int b[700][700];	// part2
int c[700][700];
int sup[700];

struct edge{
	int from;
	int to;
	int weight;
};
int main(){
	int n;
	while(cin>>n&&n!=0){
		int m;
		vector<int> supa,supb;
		vector<edge> inter;
		int dStartA[700],dEndB[700];
		for(int i=0;i<700;i++){
			for(int j=0;j<700;j++){
				a[i][j]=1e7;
				b[i][j]=1e7;
				c[i][j]=1e7;
			}
			sup[i]=0;
			a[i][i]=0;
			b[i][i]=0;
			c[i][i]=0;
			dStartA[i]=1e7;
			dEndB[i]=1e7;
		}
		
		cin>>m;
		for(int i=0;i<m;i++){
			int x1,x2,x3;
			cin>>x1>>x2>>x3;
			if(c[x1][x2]>x3) {
				c[x1][x2]=x3;
				c[x2][x1]=x3;
			}
		}
		for(int i=1;i<=n;i++){
			int tmp;
			cin>>tmp;
			sup[i]=tmp;
			if(tmp==1) supa.push_back(i);
			else supb.push_back(i);
		}
		
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(sup[i]==sup[j]){
					if(sup[i]==1){
						a[i][j]=c[i][j];
					}
					else {
						b[i][j]=c[i][j];
					}
				}
				else{
					edge e;
					e.from=i;
					e.to=j;
					e.weight=c[i][j];
					inter.push_back(e);						
				}
			}
		}
		
		for(int k=0;k<supa.size();k++){
			int mid=supa[k];
			for(int i=1;i<=n;i++){
				for(int j=1;j<=n;j++){
					if(a[i][mid]+a[mid][j]<a[i][j]) a[i][j]=a[i][mid]+a[mid][j];
				}
			}
		}
		
		for(int k=0;k<supb.size();k++){
			int mid=supb[k];
			for(int i=1;i<=n;i++){
				for(int j=1;j<=n;j++){
					if(b[i][mid]+b[mid][j]<b[i][j]) b[i][j]=b[i][mid]+b[mid][j];
				}
			}
		}
		

		for(int i=0;i<supa.size();i++){
			dStartA[supa[i]]=a[1][supa[i]];
		}		
		for(int i=0;i<supb.size();i++){
			dEndB[supb[i]]=b[supb[i]][2];
		}
		
		
		
		int min=1e7,flag=0;
		for(int i=0;i<inter.size();i++){
			int dis=0;
			if(sup[inter[i].from]==1){
				dis=dStartA[inter[i].from]+dEndB[inter[i].to]+inter[i].weight;
			}
			else {
				dis=dEndB[inter[i].from]+dStartA[inter[i].to]+inter[i].weight;
			}
			if(dis<min){
				min=dis;
				flag=1;
			}
		}
		
		if(flag==1) cout<<min<<endl;
		else cout<<-1<<endl;
		
		
	}
}
