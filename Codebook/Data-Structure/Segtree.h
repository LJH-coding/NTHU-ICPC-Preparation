template<class T,T (*op)(T,T)>
struct segment_tree{
	struct tag{
		T set,add;
		tag(T _set = 0,T _add = 0):set(_set),add(_add){}
		friend tag operator +(tag lhs,tag rhs){
			if(rhs.set)return rhs;
			if(lhs.set)return tag(lhs.set+rhs.add,0);
			return tag(0,lhs.add+rhs.add);
		}
	};
	struct node{
		T val;
		int l,r;
		node(T k = 0,int _l = -1,int _r = -1) : val(k),l(_l),r(_r){}
		tag t = tag();
		friend node operator +(const node &lhs,const node &rhs){
			if(lhs.l==-1)return rhs;
			if(rhs.l==-1)return lhs;
			return node(op(lhs.val,rhs.val),lhs.l,rhs.r);
		}
		void update(tag &tmp){
			if(tmp.set)val = tmp.set*(r-l+1);
			else val+=tmp.add*(r-l+1);
		}
		void apply(tag &tmp){
			t = t+tmp;
			update(tmp);
		}
		void push(node &a,node &b){
			if(t.set==0 and t.add==0)return;
			a.apply(t);
			b.apply(t);
			t = tag();
		}
	};
	vector<node>arr;
	inline void build(const auto &v,const int &l,const int &r,int idx = 1){
		if(idx==1)arr.assign((r-l+1)<<2,node());
		if(l==r){
			arr[idx] = node(v[l],l,r);
			return;
		}
		int m = (l+r)>>1;
		build(v,l,m,idx<<1);
		build(v,m+1,r,idx<<1|1);
		arr[idx] = arr[idx<<1]+arr[idx<<1|1];
	}
	inline void update(const int &l,const int &r,tag y,int idx = 1){
		if(l>r)return;
		if(l<=arr[idx].l and arr[idx].r<=r){
			arr[idx].apply(y);
			return;
		}
		arr[idx].push(arr[idx<<1],arr[idx<<1|1]);
		int m = (arr[idx].l+arr[idx].r)>>1;
		if(l<=m)update(l,r,y,idx<<1);
		if(r>m)update(l,r,y,idx<<1|1);
		arr[idx] = arr[idx<<1]+arr[idx<<1|1];
	}
	inline node query(const int &l,const int &r,int idx = 1){
		if(l>r)return node();
		if(l<=arr[idx].l and arr[idx].r<=r){
			return arr[idx];
		}
		int m = (arr[idx].l+arr[idx].r)>>1;
		node ans = node(),left = node(),right = node();
		if(l<=m)left = query(l,r,idx<<1);
		if(r>m)right = query(l,r,idx<<1|1);
		ans = left+right;
		return ans;
	}
};
