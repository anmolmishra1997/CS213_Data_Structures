#include <iostream>
#include <vector>
using namespace std;

#define pb push_back

int t=1;
vector<vector<int> > G,revG;
vector<int> endtimes;
vector<int> flag;
vector<int> component_ids;
int num_components=0;

void dfs1(int s){
	if(flag[s])return;
	flag[s]=true;
	int sz=revG[s].size();
	for(int i=0;i<sz;i++){
		if(!flag[revG[s][i]]){
			dfs1(revG[s][i]);
		}
	}
	endtimes[s]=t;
	t++;
}

void dfs2(int s,int id){
	if(flag[s])return;
	flag[s]=true;
	component_ids[s]=id;
	int sz=G[s].size();
	for(int i=0;i<sz;i++){
		if(!flag[G[s][i]]){
			dfs2(G[s][i],id);
		}
	}
}

int main(){
	int n,m;
	cin>>n>>m;
	endtimes.resize(n+1,-1);
	component_ids.resize(n+1,-1);
	flag.resize(n+1,false);
	G.resize(n+1);
	revG.resize(n+1);
	for(int i=0;i<m;i++){
		int x,y;
		cin>>x>>y;
		G[x].pb(y);
		revG[y].pb(x);
	}

	for(int i=1;i<=n;i++){
		if(!flag[i]){
			dfs1(i);   //stage1
		}
	}
	vector<int> order(n+1);
	for(int i=1;i<=n;i++){
		order[n-endtimes[i]+1]=i;
	}
	//for(int i=1;i<=n;i++)cout<<endtimes[i]<<" ";
	for(int i=1;i<=n;i++)flag[i]=false;

	int num_components=0;
	for(int i=1;i<=n;i++){
		if(!flag[order[i]]){
			dfs2(order[i],num_components);  //stage2
			num_components++;
		}
	}

	///////////////////////////testing part

	int q;
	cin>>q;
	for(int i=0;i<q;i++){
		int x,y;
		cin>>x>>y; 
		cout<<(component_ids[x]==component_ids[y])<<"\n";
	}


	return 0;
}