struct DSU{
	vector<int>sz;
	int n;
	DSU(int _n):n(_n){
		sz.assign(n+1,-1);
	}
	int Find(int x){
		return sz[x]<0?x:Find(sz[x]);
	}
	bool Union(int a,int b){
		int pa = Find(a),pb = Find(b);
		if(pa==pb)return 0;
		if((-sz[pa])<(-sz[pb]))swap(pa,pb);
		sz[pa]+=sz[pb];
		sz[pb] = pa;
		return 1;
	}
};
