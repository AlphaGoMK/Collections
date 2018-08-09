#include<cstdio>
#include<cstdlib>
#include<iostream>
using namespace std;
int win(char a,char b){
	if(a==b) return 0;
	if((a=='C'&&b=='J')||(a=='B'&&b=='C')||(a=='J'&&b=='B')) return 1;
	else return 2;
}
int main(){
	int cnt11,cnt12,cnt13,cnt21,cnt22,cnt23;
	int N,AWIN,EQU,ALOSE;
	char a,b;
	while(scanf("%d",&N)!=EOF){
		cnt11=cnt12=cnt13=cnt21=cnt22=cnt23=0;
		AWIN=EQU=ALOSE=0;
		while(N--){
			getchar();	// ignore blankspace
			scanf("%c %c",&a,&b);
			//cout<<a<<" "<<b<<endl;
			int r=win(a,b);
			if(r==1){
				AWIN++;
				switch(a){
					case 'B':
						cnt11++;
						break;
					case 'C':
						cnt12++;
						break;
					case 'J':
						cnt13++;
						break;		
				}
			}
			else if(r==2){
				ALOSE++;
				switch(b){
					case 'B':
						cnt21++;
						break;
					case 'C':
						cnt22++;
						break;
					case 'J':
						cnt23++;
						break;		
				}	
			}
			else EQU++;
			
		}
		
		printf("%d %d %d\n",AWIN,EQU,ALOSE);
		printf("%d %d %d\n",ALOSE,EQU,AWIN);
		if(cnt11>=cnt12&&cnt11>=cnt13) printf("B");
		else if(cnt12>=cnt11&&cnt12>=cnt13) printf("C");
		else printf("J");
		printf(" ");
		if(cnt21>=cnt22&&cnt21>=cnt23) printf("B");
		else if(cnt22>=cnt21&&cnt22>=cnt23) printf("C");
		else printf("J");
		printf("\n");
	}
	return 0;
}
