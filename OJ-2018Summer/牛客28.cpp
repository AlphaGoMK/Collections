#include<cstdio>
#include<cstring>

int arr[5][5];
int op1(int x,int y){
	int tmp[2][2];
	int toki=0,tokj=0;
	for(int i=x-1;i<x-1+2;i++){
		for(int j=y-1;j<y-1+2;j++){
			tmp[toki][tokj]=arr[i][j];
			tokj++;
		}
		tokj=0;
		toki++;
	}
	
	arr[x-1][y-1]=tmp[1][0];
	arr[x-1+1][y-1]=tmp[1][1];
	arr[x-1][y-1+1]=tmp[0][0];
	arr[x-1+1][y-1+1]=tmp[0][1];
	
	return 0;
}

int op2(int x,int y){
	int tmp[3][3];
	int toki=0,tokj=0;
	for(int i=x-1;i<x-1+3;i++){
		for(int j=y-1;j<y-1+3;j++){
			tmp[toki][tokj]=arr[i][j];
			tokj++;
		}
		tokj=0;
		toki++;
	}
	
	arr[x-1][y-1]=tmp[2][0];
	arr[x-1+1][y-1]=tmp[2][1];
	arr[x-1+2][y-1]=tmp[2][2];
	arr[x-1][y-1+1]=tmp[1][0];
	arr[x-1+1][y-1+1]=tmp[1][1];
	arr[x-1+2][y-1+1]=tmp[1][2];
	arr[x-1][y-1+2]=tmp[0][0];
	arr[x-1+1][y-1+2]=tmp[0][1];
	arr[x-1+2][y-1+2]=tmp[0][2];
	
	return 0;
}

int op3(int x,int y){
	int tmp[2][2];
	int toki=0,tokj=0;
	for(int i=x-1;i<x-1+2;i++){
		for(int j=y-1;j<y-1+2;j++){
			tmp[toki][tokj]=arr[i][j];
			tokj++;
		}
		tokj=0;
		toki++;
	}
	
	arr[x-1][y-1]=tmp[0][1];
	arr[x-1+1][y-1]=tmp[0][0];
	arr[x-1][y-1+1]=tmp[1][1];
	arr[x-1+1][y-1+1]=tmp[1][0];
	
	return 0;
}

int op4(int x,int y){
	int tmp[3][3];
	int toki=0,tokj=0;
	for(int i=x-1;i<x-1+3;i++){
		for(int j=y-1;j<y-1+3;j++){
			tmp[toki][tokj]=arr[i][j];
			tokj++;
		}
		tokj=0;
		toki++;
	}
	
	arr[x-1][y-1]=tmp[0][2];
	arr[x-1+1][y-1]=tmp[0][1];
	arr[x-1+2][y-1]=tmp[0][0];
	arr[x-1][y-1+1]=tmp[1][2];
	arr[x-1+1][y-1+1]=tmp[1][1];
	arr[x-1+2][y-1+1]=tmp[1][0];
	arr[x-1][y-1+2]=tmp[2][2];
	arr[x-1+1][y-1+2]=tmp[2][1];
	arr[x-1+2][y-1+2]=tmp[2][0];
	
	return 0;
}

int main(){
	memset(arr,0,sizeof(arr));
	while(scanf("%d",&arr[0][0])!=EOF){
		scanf("%d%d%d%d",&arr[0][1],&arr[0][2],&arr[0][3],&arr[0][4]);
		for(int i=1;i<5;i++){
			for(int j=0;j<5;j++){
				scanf("%d",&arr[i][j]);
			}
		}
		

		int x,y,a,b;
		scanf("%d%d%d%d",&a,&b,&x,&y);
		if(a==1&&b==2) op1(x,y);
		else if(a==1&&b==3) op2(x,y);
		else if(a==2&&b==2) op3(x,y);
		else op4(x,y);
		
		for(int i=0;i<5;i++){
			for(int j=0;j<5;j++){
				if(j==0) printf("%d",arr[i][j]);
				else printf(" %d",arr[i][j]);
			}
			printf("\n");
		}	
	}
	return 0;
}
