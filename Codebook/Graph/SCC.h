struct SCC{
	int n,cnt = 0,dfn_cnt = 0;
	vector<int>sz,scc,low,dfn;
	stack<int>st;
	vector<bool>vis;
	SCC(int _n):n(_n){
		sz.resize(n+5),scc.resize(n+5),low.resize(n+5),dfn.resize(n+5),vis.resize(n+5);
	}
	inline void build(const vector<vector<int>>&g,int u,int dis = 1){
		low[u] = dfn[u] = ++dfn_cnt,vis[u] = 1;
		st.push(u);
		for(auto v:g[u]){
			if(!dfn[v]){
				build(g,v,dis+1);
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
	}
	vector<vector<int>> compress(const vector<pii>&e,vector<int>&ind){
		vector<vector<int>>ans(n+5);
		for(auto [u,v]:e){
			if(scc[u]==scc[v])continue;
			ans[scc[u]].pb(scc[v]);
			ind[scc[v]]++;
		}
		return ans;
	}
};
