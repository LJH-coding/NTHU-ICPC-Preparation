template<class T>
struct Dinic{
	struct edge{
		int to;
		T cap;
		edge(int _to, T _cap) : to(_to), cap(_cap) {}
	};
	int n;
	vector<edge> edges;
	vector<vector<int>> g;
	vector<int> cur, h;
	Dinic(int _n) : n(_n+1), g(_n+1) {}
	void add_edge(int u, int v, T cap){
		g[u].push_back(edges.size());
		edges.push_back(edge(v,cap));
		g[v].push_back(edges.size());
		edges.push_back(edge(u,0));
	}
	bool bfs(int s,int t){
		h.assign(n, -1);
		h[s] = 0;
		queue<int> que;
		que.push(s);
		while(!que.empty()) {
			int u = que.front();
			que.pop();
			for(auto id : g[u]) {
				const edge& e = edges[id];
				int v = e.to;
				if(e.cap > 0 && h[v] == -1) {
					h[v] = h[u] + 1;
					if(v == t) {
						return 1;
					}
					que.push(v);
				}
			}
		}
		return 0;
	}
	T dfs(int u, int t, T f) {
		if(u == t) {
			return f;
		}
		T r = f;
		for(int& i = cur[u]; i < (int) g[u].size(); ++i) {
			int id = g[u][i];
			const edge& e = edges[id];
			int v = e.to;
			if(e.cap > 0 && h[v] == h[u] + 1) {
				T send = dfs(v, t, min(r, e.cap));
				edges[id].cap -= send;
				edges[id ^ 1].cap += send;
				r -= send;
				if(r == 0) {
					return f;
				}
			}
		}
		return f - r;
	}
	T flow(int s, int t, T f = numeric_limits<T>::max()) {
		T ans = 0;
		while(f > 0 && bfs(s, t)) {
			cur.assign(n, 0);
			T send = dfs(s, t, f);
			ans += send;
			f -= send;
		}
		return ans;
	}
};
