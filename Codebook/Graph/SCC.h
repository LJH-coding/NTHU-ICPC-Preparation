struct SCC{
	int n,cnt = 0,dfn_cnt = 0;
	vector<vector<int>>g;
	vector<int>sz,scc,low,dfn;
	stack<int>st;
	vector<bool>vis;
	SCC(int _n = 0) : n(_n){
		sz.resize(n+5),scc.resize(n+5),low.resize(n+5),dfn.resize(n+5),vis.resize(n+5);
		g.resize(n+5);
	}
	inline void add_edge(int u, int v){
		g[u].push_back(v);
	}
	inline void build(){
		function<void(int, int)>dfs = [&](int u,int dis){
			low[u] = dfn[u] = ++dfn_cnt,vis[u] = 1;
			st.push(u);
			for(auto v:g[u]){
				if(!dfn[v]){
					dfs(v, dis+1);
					low[u] = min(low[u],low[v]);
				}
				else if(vis[v]){
					low[u] = min(low[u],dfn[v]);
				}
			}
			if(low[u]==dfn[u]){
				++cnt;
				while(vis[u]){
					auto v = st.top();
					st.pop();
					vis[v] = 0;
					scc[v] = cnt;
					sz[cnt]++;
				}
			}
		};
		for(int i = 0;i<=n;++i){
			if(!scc[i]){
				dfs(i, 1);
			}
		}
	}
	vector<vector<int>> compress(){
		vector<vector<int>>ans(cnt+1);
		for(int u = 0;u<=n;++u){
			for(auto v:g[u]){
				if(scc[u] == scc[v]){
					continue;
				}
				ans[scc[u]].push_back(scc[v]);
			}
		}
		for(int i = 0;i<=cnt;++i){
			sort(ans[i].begin(), ans[i].end());
			ans[i].erase(unique(ans[i].begin(), ans[i].end()), ans[i].end());
		}
		return ans;
	}
};
