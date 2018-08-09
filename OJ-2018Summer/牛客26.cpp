#include<cstdio>
using namespace std;

int  main(){
	int n;
	while(scanf("%d",&n)!=EOF){
		int odd=0,even=0,x=0;
		while(n--){
			scanf("%d",&x);
			if(x%2==0) even++;
			else odd++;
		}
		if(even>odd) printf("%s\n","NO");
		else printf("%s\n","YES");
	}
	return 0;
}
