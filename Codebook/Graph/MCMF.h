template<class Cap_t, class Cost_t>
class MCMF {
public:
	struct Edge {
		int from;
		int to;
		Cap_t cap;
		Cost_t cost;
		Edge(int u, int v, Cap_t _cap, Cost_t _cost) : from(u), to(v), cap(_cap), cost(_cost) {}
	};

	static constexpr Cap_t EPS = static_cast<Cap_t>(1e-9);

	int n;
	vector<Edge> edges;
	vector<vector<int>> g;
	vector<Cost_t> d;
	vector<bool> in_queue;
	vector<int> previous_edge;

	MCMF() {}
	MCMF(int _n) : n(_n+1), g(_n+1), d(_n+1), in_queue(_n+1), previous_edge(_n+1) {}

	void add_edge(int u, int v, Cap_t cap, Cost_t cost) {
		assert(0 <= u && u < n);
		assert(0 <= v && v < n);
		g[u].push_back(edges.size());
		edges.emplace_back(u, v, cap, cost);
		g[v].push_back(edges.size());
		edges.emplace_back(v, u, 0, -cost);
	}

	bool spfa(int s, int t) {
		bool found = false;
		fill(d.begin(), d.end(), numeric_limits<Cost_t>::max());
		d[s] = 0;
		in_queue[s] = true;
		queue<int> que;
		que.push(s);
		while(!que.empty()) {
			int u = que.front();
			que.pop();
			if(u == t) {
				found = true;
			}
			in_queue[u] = false;
			for(auto& id : g[u]) {
				const Edge& e = edges[id];
				if(e.cap > EPS && d[u] + e.cost < d[e.to]) {
					d[e.to] = d[u] + e.cost;
					previous_edge[e.to] = id;
					if(!in_queue[e.to]) {
						que.push(e.to);
						in_queue[e.to] = true;
					}
				}
			}
		}
		return found;
	}

	pair<Cap_t, Cost_t> flow(int s, int t, Cap_t f = numeric_limits<Cap_t>::max()) {
		assert(0 <= s && s < n);
		assert(0 <= t && t < n);
		Cap_t cap = 0;
		Cost_t cost = 0;
		while(f > 0 && spfa(s, t)) {
			Cap_t send = f;
			int u = t;
			while(u != s) {
				const Edge& e = edges[previous_edge[u]];
				send = min(send, e.cap);
				u = e.from;
			}
			u = t;
			while(u != s) {
				Edge& e = edges[previous_edge[u]];
				e.cap -= send;
				Edge& b = edges[previous_edge[u] ^ 1];
				b.cap += send;
				u = e.from;
			}
			cap += send;
			f -= send;
			cost += send * d[t];
		}
		return make_pair(cap, cost);
	}
};
