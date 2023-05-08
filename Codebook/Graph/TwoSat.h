struct two_sat{
	SCC s;
	vector<bool>ans;
	int have_ans = 0;
	int n;
	two_sat(int _n) : n(_n) {
		ans.resize(n+1);
		s = SCC(2*n);
	}
	int inv(int x){
		if(x>n)return x-n;
		return x+n;
	}
	void add_or_clause(int u, bool x, int v, bool y){
		if(!x)u = inv(u);
		if(!y)v = inv(v);
		s.add_edge(inv(u), v);
		s.add_edge(inv(v), u);
	}
	void check(){
		if(have_ans!=0)return;
		s.build();
		for(int i = 0;i<=n;++i){
			if(s.scc[i]==s.scc[inv(i)]){
				have_ans = -1;
				return;
			}
			ans[i] = (s.scc[i]<s.scc[inv(i)]);
		}
		have_ans = 1;
	}
};
