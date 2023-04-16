template<class S,
		 S (*node_pull)(S, S),
		 S (*node_init)(),
		 class T,
		 S (*mapping)(S, T),
		 T (*tag_pull)(T, T),
		 T (*tag_init)()>
struct segment_tree{
	struct node{
		S seg;
		T tag = tag_init();
		int l,r;
		node(S _seg = node_init(),int _l = -1,int _r = -1) : seg(_seg), l(_l), r(_r){}
		friend node operator +(const node &lhs,const node &rhs){
			if(lhs.l==-1)return rhs;
			if(rhs.l==-1)return lhs;
			return node(node_pull(lhs.seg,rhs.seg),lhs.l,rhs.r);
		};
	};
	vector<node>arr;
	void all_apply(int idx,T t){
		arr[idx].seg = mapping(arr[idx].seg, t);
		arr[idx].tag = tag_pull(arr[idx].tag, t);
	}
	void push(int idx){
		all_apply(idx<<1, arr[idx].tag);
		all_apply(idx<<1|1, arr[idx].tag);
		arr[idx].tag = tag_init();
	}
	inline void build(const vector<S> &v,const int &l,const int &r,int idx = 1){
		if(idx==1)arr.resize((r-l+1)<<2);
		if(l==r){
			arr[idx].seg = v[l];
			arr[idx].tag = tag_init();
			arr[idx].l = arr[idx].r = l;
			return;
		}
		int m = (l+r)>>1;
		build(v,l,m,idx<<1);
		build(v,m+1,r,idx<<1|1);
		arr[idx] = arr[idx<<1]+arr[idx<<1|1];
	}
	inline void update(const int &ql,const int &qr,T t,int idx = 1){
		assert(ql<=qr);
		if(ql<=arr[idx].l and arr[idx].r<=qr){
			all_apply(idx, t);
			return;
		}
		push(idx);
		int m = (arr[idx].l+arr[idx].r)>>1;
		if(ql<=m)update(ql,qr,t,idx<<1);
		if(qr>m)update(ql,qr,t,idx<<1|1);
		arr[idx] = arr[idx<<1]+arr[idx<<1|1];
	}
	inline S query(const int &ql,const int &qr,int idx = 1){
		assert(ql<=qr);
		if(ql<=arr[idx].l and arr[idx].r<=qr){
			return arr[idx].seg;
		}
		push(idx);
		int m = (arr[idx].l+arr[idx].r)>>1;
		S ans = node_init(),lhs = node_init(),rhs = node_init();
		if(ql<=m)lhs = query(ql,qr,idx<<1);
		if(qr>m)rhs = query(ql,qr,idx<<1|1);
		ans = node_pull(lhs,rhs);
		return ans;
	}
};
