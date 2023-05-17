struct heavy_light_decomposition{
	int n;
	vector<int>dep,father,sz,mxson,topf,id;
	vector<vector<int>>g;
	heavy_light_decomposition(int _n = 0) : n(_n) {
		g.resize(n+5);
		dep.resize(n+5);
		father.resize(n+5);
		sz.resize(n+5);
		mxson.resize(n+5);
		topf.resize(n+5);
		id.resize(n+5);
	}
	void add_edge(int u, int v){
		g[u].push_back(v);
		g[v].push_back(u);
	}
	void dfs(int u,int p){
		dep[u] = dep[p]+1;
		father[u] = p;
		sz[u] = 1;
		mxson[u] = 0;
		for(auto v:g[u]){
			if(v==p)continue;
			dfs(v,u);
			sz[u]+=sz[v];
			if(sz[v]>sz[mxson[u]])mxson[u] = v;
		}
	}
	void dfs2(int u,int top){
		static int idn = 0;
		topf[u] = top;
		id[u] = ++idn;
		if(mxson[u])dfs2(mxson[u],top);
		for(auto v:g[u]){
			if(v!=father[u] and v!=mxson[u]){
				dfs2(v,v);
			}
		}
	}
	void build(int root){
		dfs(root,0);
		dfs2(root,root);
	}
	vector<pair<int, int>> path(int u,int v){
		vector<pair<int, int>>ans;
		while(topf[u]!=topf[v]){
			if(dep[topf[u]]<dep[topf[v]])swap(u,v);
			ans.push_back({id[topf[u]], id[u]});
			u = father[topf[u]];
		}
		if(id[u]>id[v])swap(u,v);
		ans.push_back({id[u], id[v]});
		return ans;
	}
};
