struct LCA {
	LCA() : LCA(0) {}
	LCA(int _n) : n(_n), g(_n) {}
	static pii __lca_op(pii a, pii b) { return min(a, b); }
	void add_edge(int u, int v) {
		assert(0 <= u && u < n);
		assert(0 <= v && v < n);
		g[u].PB(v); g[v].PB(u);
	}
	void build(int root = 0) {
		assert(0 <= root && root < n);
		depth.assign(n, 0);
		parent.assign(n, -1);
		subtree_size.assign(n, 1);
		euler.reserve(2 * n - 1);
		first_occurrence.assign(n, 0);
		tour_list.reserve(n);
		tour_start.assign(n, 0);
		function<void(int, int, int)> dfs = [&](int u, int p, int d) {
			parent[u] = p;
			depth[u] = d;
			first_occurrence[u] = SZ(euler);
			euler.PB(u);
			pii heavy = {-1, -1};
			for(auto& v : g[u]) {
				if(v == p) continue;
				dfs(v, u, d + 1);
				subtree_size[u] += subtree_size[v];
				if(subtree_size[v] > heavy.F) heavy = {subtree_size[v], v};
				euler.PB(u);
			}
			sort(ALL(g[u]), [&](int a, int b) {
				return subtree_size[a] > subtree_size[b];
			});
		};
		dfs(root, -1, 0);
		heavy_root.assign(n, 0);
		function<void(int, bool)> dfs2 = [&](int u, bool is_heavy) {
			tour_start[u] = SZ(tour_list);
			tour_list.PB(u);
			heavy_root[u] = (is_heavy ? heavy_root[parent[u]] : u);
			bool heavy = true;
			for(auto& v : g[u]) {
				if(v == parent[u]) continue;
				dfs2(v, heavy);
				heavy = false;
			}
		};
		dfs2(root, false);
		vector<pii> route;
		route.reserve(SZ(euler));
		for(auto& u : euler) route.EB(depth[u], u);
		st = sparse_table<pii, __lca_op>(route);
	}
	inline int dist(int u, int v) const {
		return depth[u] + depth[v] - 2 * depth[lca(u, v)];
	}
	pair<int, array<int, 2>> get_diameter() const {
		pii u_max = {-1, -1};
		pii ux_max = {-1, -1};
		pair<int, array<int, 2>> uxv_max = {-1, {-1, -1}};
		for(int u : euler) {
			u_max = max(u_max, {depth[u], u});
			ux_max = max(ux_max, {u_max.F - 2 * depth[u], u_max.S});
			uxv_max = max(uxv_max, {ux_max.F + depth[u], {ux_max.S, u}});
		}
		return uxv_max;
	}
	inline int kth_ancestor(int u, int k) const {
		if(depth[u] < k) return -1;
		while(k > 0) {
			int root = heavy_root[u];
			if(depth[root] <= depth[u] - k) return tour_list[tour_start[u] - k];
			k -= depth[u] - depth[root] + 1;
			u = parent[root];
		}
		return u;
	}
	inline int kth_node_on_path(int a, int b, int k) const {
		int z = lca(a, b);
		int fi = depth[a] - depth[z], se = depth[b] - depth[z];
		assert(0 <= k && k <= fi + se);
		if(k < fi) return kth_ancestor(a, k);
		else return kth_ancestor(b, fi + se - k);
	}
	int lca(int u, int v) const {
		assert(0 <= u && u < n);
		assert(0 <= v && v < n);
		int l = first_occurrence[u], r = first_occurrence[v];
		return st.prod(min(l, r), max(l, r)).S;
	}
	int n;
	vector<vector<int>> g;
	vector<int> parent, depth, subtree_size;
	vector<int> euler, first_occurrence, tour_list, tour_start, heavy_root;
	sparse_table<pii, __lca_op> st;
};
