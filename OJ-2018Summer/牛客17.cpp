#include<iostream>
#include<vector>
using namespace std;

vector<string> proxy;
vector<string> server;
vector<int> show[1010]; // 第一次出现的时间 
int main(){
	int n,m;
	while(cin>>n&&!cin.eof()){
		string s;
		while(n--){
			cin>>s;
			proxy.push_back(s);
		}
		n=proxy.size();
		cin>>m;
		while(m--){
			cin>>s;
			server.push_back(s);
		}
		m=server.size();
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				if(server[j]==proxy[i]){
					show[i].push_back(j);
				}
			}
			show[i].push_back(6000);	//每个都最后加正无穷，表征之后不再出现（出现位置为正无穷） 
		}
		
		//for(int i=0;i<n;i++){
		//	cout<<" "<<proxy[i]<<": ";
		//	for(int j=0;j<show[i].size();j++) cout<<show[i].at(j)<<" ";
		//	cout<<endl;
		//}
		
		int sum=0,ans=0;
		while(sum<m){
			int max=-1;
			for(int i=0;i<n;i++){
				//cout<<i<<": "<<show[i].front()<<endl;
				if(show[i].front()>max) max=show[i].front();
			}
			if(max==sum) {	// 最大即为0，即只有一种选择 ，误解 proxy=1 server=11111 
				ans=0;
				break;
			}
			sum=max;
			
			//cout<<"sum: "<<sum<<endl;
			
			ans++;
			for(int i=0;i<n;i++){
				vector<int>::iterator last=show[i].begin()+(show[i].size()-1);	// end是最后一个元素的下一个位置，所以erase（begin，end）会全删
																				// begin(+size()-1)才是最后一个元素的迭代器位置 
				for(vector<int>::iterator it=show[i].begin();it!=show[i].end();it++){
					if(*it>=sum) {	// 找大于等于sum的。每次sum值表示现在改选那个位置之前的proxy，等于表示该元素最早在应选位置之前出现，即这个元素是需要替换的元素
									// 等于即需要选出6之前应该使用哪个代理，而6的front也应该和sum相同，表示最早出现即应选位置，需要避开6. 即如果选择6，则下一个sum位置是不变的 
						last=it;
						break;
					}
				}
				
				show[i].erase(show[i].begin(),last);	// delete from [begin() to last-1], last is not included
				
				//cout<<" "<<proxy[i]<<": ";
				//for(int j=0;j<show[i].size();j++) cout<<show[i].at(j)<<" ";
				//cout<<endl;
			}
			//cout<<sum<<endl;
			
		}
		ans--;	//第一次 
		
		cout<<ans<<endl;
		
		for(int i=0;i<n;i++){
			show[i].clear();
		}
		proxy.clear();
		server.clear();
	}
}
