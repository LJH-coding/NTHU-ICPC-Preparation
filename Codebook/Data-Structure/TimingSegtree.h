template<class T,class D>struct timing_segment_tree{
	struct node{
		int l,r;
		vector<T>opt;
	};
	vector<node>arr;
	void build(int l,int r,int idx = 1){
		if(idx==1)arr.resize((r-l+1)<<2);
		if(l==r){
			arr[idx].l = arr[idx].r = l;
			arr[idx].opt.clear();
			return;
		}
		int m = (l+r)>>1;
		build(l,m,idx<<1);
		build(m+1,r,idx<<1|1);
		arr[idx].l = l,arr[idx].r = r;
		arr[idx].opt.clear();
	}
	void update(int ql,int qr,T k,int idx = 1){
		if(ql<=arr[idx].l and arr[idx].r<=qr){
			arr[idx].opt.push_back(k);
			return;
		}
		int m = (arr[idx].l+arr[idx].r)>>1;
		if(ql<=m)update(ql,qr,k,idx<<1);
		if(qr>m)update(ql,qr,k,idx<<1|1);
	}
	void dfs(D &d,vector<int>&ans,int idx = 1){
		int cnt = 0;
		for(auto [a,b]:arr[idx].opt){
			if(d.Union(a,b))cnt++;
		}
		if(arr[idx].l==arr[idx].r)ans[arr[idx].l] = d.comps;
		else{
			dfs(d,ans,idx<<1);
			dfs(d,ans,idx<<1|1);
		}
		while(cnt--)d.undo();
	}
};
