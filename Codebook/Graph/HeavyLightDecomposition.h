struct heavy_light_decomposition{
	int n,root;
	vector<int>dep,father,sz,mxson,topf,id;
	segment_tree<int>seg;
	heavy_light_decomposition(int _n,int _root,vector<vector<int>>&g): n(_n),root(_root){
		seg.init(n+5);
		dep.resize(n+5);
		father.resize(n+5);
		sz.resize(n+5);
		mxson.resize(n+5);
		topf.resize(n+5);
		id.resize(n+5);
		function<void(int,int)>dfs = [&](int u,int p){
			dep[u] = dep[p]+1;
			father[u] = p;
			sz[u] = 1;
			mxson[u] = 0;
			for(auto v:g[u]){
				if(v!=p){
					dfs(v,u);
					sz[u]+=sz[v];
					if(sz[v]>sz[mxson[u]])mxson[u] = v;
				}
			}
		};
		function<void(int,int)>dfs2 = [&](int u,int top){
			static int idn = 0;
			topf[u] = top;
			id[u] = ++idn;
			if(mxson[u])dfs2(mxson[u],top);
			for(auto v:g[u]){
				if(v!=father[u] and v!=mxson[u]){
					dfs2(v,v);
				}
			}
		};
		dfs(root,0);
		dfs2(root,root);
	}
	int query(int u,int v){
		int ans = 0;
		while(topf[u]!=topf[v]){
			if(dep[topf[u]]<dep[topf[v]])swap(u,v);
			ans+=seg.query(id[topf[u]],id[u]).sum;
			u = father[topf[u]];
		}
		if(id[u]>id[v])swap(u,v);
		ans+=seg.query(id[u],id[v]).sum;
		return ans;
	}
	void update(int u,int v,int val){
		while(topf[u]!=topf[v]){
			if(dep[topf[u]]<dep[topf[v]])swap(u,v);
			seg.update(id[topf[u]],id[u],val);
			u = father[topf[u]];
		}
		if(id[u]>id[v])swap(u,v);
		seg.update(id[u],id[v],val);
	}
};
