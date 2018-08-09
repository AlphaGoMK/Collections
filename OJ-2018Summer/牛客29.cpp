#include<cstdio>
#include<cstring>

int mat[10][10],mat2[10][10];
int rank=0;

int solve(){
	int flag=0;
	for(int i=0;i<rank;i++){
		for(int j=0;j<rank;j++){
			if(mat[i][j]==mat2[i][j]) flag=1;
			else {
				flag=0;
				break;
			}
		}
		if(flag==0) break;
	}	
	if(flag==1) return 0;
	
	for(int i=0;i<rank;i++){
		for(int j=0;j<rank;j++){
			if(mat[i][j]==mat2[j][rank-1-i]) flag=1;
			else {
				flag=0;
				break;
			}	
		}
		if(flag==0) break;
	}
	if(flag==1) return 90;
	
	for(int i=0;i<rank;i++){
		for(int j=0;j<rank;j++){
			if(mat[i][j]==mat2[rank-1-i][rank-1-j]) flag=1;
			else {
				flag=0;
				break;
			}	
		}
		if(flag==0) break;
	}
	if(flag==1) return 180;
	
		for(int i=0;i<rank;i++){
		for(int j=0;j<rank;j++){
			if(mat[i][j]==mat2[rank-1-j][i]) flag=1;
			else {
				flag=0;
				break;
			}
		}
		if(flag==0) break;
	}
	if(flag==1) return 270;
	return -1;
}
int main(){
	while(scanf("%d",&rank)!=EOF){
		for(int i=0;i<rank;i++){
			for(int j=0;j<rank;j++){
				scanf("%d",&mat[i][j]);
			}
		}
		for(int i=0;i<rank;i++){
			for(int j=0;j<rank;j++){
				scanf("%d",&mat2[i][j]);
			}
		}
		
		printf("%d\n",solve());
	}
	return 0;
}
