vector<vector<int>>g,dp;
vector<int>deep;
void build(int root,int n){
	dp.assign(25,vector<int>(n+5));
	deep.assign(n+5,0);
	function<void(int,int,int)>dfs = [&](int u,int p,int dis){
		dp[0][u] = p;
		deep[u] = dis;
		for(auto v:g[u]){
			if(v==p)continue;
			dfs(v,u,dis+1);
		}
	};
	dfs(root,0,1);
	for(int i = 1;i<=20;++i){
		for(int j = 1;j<=n;++j){
			dp[i][j] = dp[i-1][dp[i-1][j]];
		}
	}
}
int LCA(int u,int v){
	if(deep[u]<deep[v])swap(u,v);
	for(int i = 20;i>=0;--i){
		if(deep[dp[i][u]]>=deep[v])
			u = dp[i][u];
	}
	if(u==v)return u;
	for(int i = 20;i>=0;--i){
		if(dp[i][u]!=dp[i][v])u = dp[i][u],v = dp[i][v];
	}
	return dp[0][u];
}
