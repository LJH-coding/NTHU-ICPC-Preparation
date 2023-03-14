vector<vector<int>>g;
vector<int>sz,tmp;
vector<bool>vis;//visit_centroid
int tree_centroid(int u,int n){
	function<void(int,int)>dfs1 = [&](int u,int p){
		sz[u] = 1;
		for(auto v:g[u]){
			if(v==p)continue;
			if(vis[v])continue;
			dfs1(v,u);
			sz[u]+=sz[v];
		}
	};
	function<int(int,int)>dfs2 = [&](int u,int p){
		for(auto v:g[u]){
			if(v==p)continue;
			if(vis[v])continue;
			if(sz[v]*2<n)continue;
			return dfs2(v,u);
		}
		return u;
	};
	dfs1(u,-1);
	return dfs2(u,-1);
}
int cal(int u,int p = -1,int deep = 1){
	int ans = 0;
	tmp.pb(deep);
	sz[u] = 1;
	for(auto v:g[u]){
		if(v==p)continue;
		if(vis[v])continue;
		ans+=cal(v,u,deep+1);
		sz[u]+=sz[v];
	}
	//calcuate the answer
	return ans;
}
int centroid_decomposition(int u,int tree_size){
	int center = tree_centroid(u,tree_size);
	vis[center] = 1;
	int ans = 0;
	for(auto v:g[center]){
		if(vis[v])continue;
		ans+=cal(v);
		for(int i = sz(tmp)-sz[v];i<sz(tmp);++i){
			//update
		}
	}
	while(!tmp.empty()){
		//roll_back(tmp.back())
		tmp.pop_back();
	}
	for(auto v:g[center]){
		if(vis[v])continue;
		ans+=centroid_decomposition(v,sz[v]);
	}
	return ans;
}
