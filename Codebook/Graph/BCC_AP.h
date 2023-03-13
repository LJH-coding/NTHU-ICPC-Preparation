struct BCC_AP{
	int dfn_cnt = 0,bcc_cnt = 0,n;
	vector<int>dfn,low,ap,bcc_id;
	stack<int>st;
	vector<bool>vis,is_ap;
	vector<vector<int>>bcc;
	BCC_AP(int _n):n(_n){
		dfn.resize(n+5),low.resize(n+5),bcc.resize(n+5),vis.resize(n+5),is_ap.resize(n+5),bcc_id.resize(n+5);
	}
	inline void build(const vector<vector<int>>&g,int u,int p = -1){
		int child = 0;
		dfn[u] = low[u] = ++dfn_cnt;
		st.push(u);
		vis[u] = 1;
		if(g[u].empty() and p==-1){
			bcc_id[u] = ++bcc_cnt;
			bcc[bcc_cnt].push_back(u);
			return;
		}
		for(auto v:g[u]){
			if(v==p)continue;
			if(!dfn[v]){
				build(g,v,u);
				child++;
				if(dfn[u]<=low[v]){
					is_ap[u] = 1;
					bcc_id[u] = ++bcc_cnt;
					bcc[bcc_cnt].push_back(u);
					while(vis[v]){
						bcc_id[st.top()] = bcc_cnt;
						bcc[bcc_cnt].push_back(st.top());
						vis[st.top()] = 0;
						st.pop();
					}
				}
				low[u] = min(low[u],low[v]);
			}
			low[u] = min(low[u],dfn[v]);
		}
		if(p==-1 and child<2)is_ap[u] = 0;
		if(is_ap[u])ap.push_back(u);
	}
};
