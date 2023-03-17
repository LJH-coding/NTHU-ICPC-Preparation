int rk[200001] = {};
struct Persistent_DSU{
	rope<int>*p;
	int n;
	Persistent_DSU(int _n = 0):n(_n){
		if(n==0)return;
		p = new rope<int>;
		int tmp[n+1] = {};
		for(int i = 1;i<=n;++i)tmp[i] = i;
		p->append(tmp,n+1);
	}
	Persistent_DSU(const Persistent_DSU &tmp){
		p = new rope<int>(*tmp.p);
		n = tmp.n;
	}
	int Find(int x){
		int px = p->at(x);
		return px==x?x:Find(px);
	}
	bool Union(int a,int b){
		int pa = Find(a),pb = Find(b);
		if(pa==pb)return 0;
		if(rk[pa]<rk[pb])swap(pa,pb);
		p->replace(pb,pa);
		if(rk[pa]==rk[pb])rk[pa]++;
		return 1;
	}
};
