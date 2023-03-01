struct dsu_undo{
	vector<int>sz,p;
	int comps;
	dsu_undo(int n){
		sz.assign(n+5,1);
		p.resize(n+5);
		for(int i = 1;i<=n;++i)p[i] = i;
		comps = n;
	}
	vector<pair<int,int>>opt;
	int Find(int x){
		return x==p[x]?x:Find(p[x]);
	}
	bool Union(int a,int b){
		int pa = Find(a),pb = Find(b);
		if(pa==pb)return 0;
		if(sz[pa]<sz[pb])swap(pa,pb);
		sz[pa]+=sz[pb];
		p[pb] = pa;
		opt.push_back({pa,pb});
		comps--;
		return 1;
	}
	void undo(){
        auto [pa,pb] = opt.back();
        opt.pop_back();
        p[pb] = pb;
        sz[pa]-=sz[pb];
        comps++;
	}
};
