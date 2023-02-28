template<class T>struct segment_tree{
	struct node{
		int l,r,mx_id,mn_id;
		T lz,lz2;
		T sum,mx,mn;
		node(){
			l = r = lz  = lz2 = sum = mx = mn = 0,mx_id = -1,mn_id = -1;
		}
		friend bool operator ==(node a,node b){
			return (a.l==b.l and a.r==b.r);
		}
	};
	vector<node>arr;
	inline void pull(node &ans,const node &left,const node &right){
		if(left==node())ans = right;
		else if(right==node())ans = left;
		else{
		ans.mx = max(left.mx,right.mx);
		ans.mx_id = (left.mx>right.mx?left.mx_id:right.mx_id);
		ans.mn = min(left.mn,right.mn);
		ans.mn_id = (left.mn<right.mn?left.mn_id:right.mn_id);
		ans.sum = left.sum+right.sum;
		ans.l = left.l,ans.r = right.r;
		}
	}inline void pull(const int &idx){
		pull(arr[idx],arr[idx<<1],arr[idx<<1|1]);
	}
	inline void push(const int &idx){
		int m = (arr[idx].l+arr[idx].r)>>1;
		if(arr[idx].lz){
			arr[idx<<1].mn = arr[idx<<1].mx = arr[idx].lz;
			arr[idx<<1].sum = (m-arr[idx].l+1)*arr[idx].lz;
			arr[idx<<1].lz = arr[idx].lz;
			arr[idx<<1].lz2 = 0;
			arr[idx<<1|1].mn = arr[idx<<1|1].mx = arr[idx].lz;
			arr[idx<<1|1].sum = (arr[idx].r-m)*arr[idx].lz;
			arr[idx<<1|1].lz = arr[idx].lz;
			arr[idx<<1|1].lz2 = 0;
			arr[idx].lz = 0;
			arr[idx].lz2 = 0;
		}
		else if(arr[idx].lz2){
			arr[idx<<1].mn += arr[idx].lz2;
			arr[idx<<1].mx += arr[idx].lz2;
			arr[idx<<1].sum+=(m-arr[idx].l+1)*arr[idx].lz2;
			if(arr[idx<<1].lz==0)arr[idx<<1].lz2+=arr[idx].lz2;
			else{
				arr[idx<<1].lz+=arr[idx].lz2;
				arr[idx<<1].lz2 = 0;
			}
			arr[idx<<1|1].mn += arr[idx].lz2;
			arr[idx<<1|1].mx += arr[idx].lz2;
			arr[idx<<1|1].sum+=(arr[idx].r-m)*arr[idx].lz2;
			if(arr[idx<<1|1].lz==0)arr[idx<<1|1].lz2+=arr[idx].lz2;
			else{
				arr[idx<<1|1].lz+=arr[idx].lz2;
				arr[idx<<1|1].lz2 = 0;
			}
			arr[idx].lz2 = 0;
		}
	}
	inline void build(const vector<T>&v,const int &l,const int &r,int idx = 1){
		if(idx==1)arr.assign((r-l+1)<<2,node());
		if(l==r){
			arr[idx].sum = arr[idx].mn = arr[idx].mx = v[l];
			arr[idx].l = arr[idx].r = arr[idx].mx_id = arr[idx].mn_id = l;
			return;
		}
		int m = (l+r)>>1;
		build(v,l,m,idx<<1);
		build(v,m+1,r,idx<<1|1);
		pull(idx);
	}
	inline void set(const int &l,const int &r,const T &y,int idx = 1){
		if(l>r)return;
		if(l<=arr[idx].l and arr[idx].r<=r){
			arr[idx].sum = (arr[idx].r-arr[idx].l+1)*y;
			arr[idx].mn = arr[idx].mx = y;
			arr[idx].lz = y;
			arr[idx].lz2 = 0;
			return;
		}
		push(idx);
		int m = (arr[idx].l+arr[idx].r)>>1;
		if(l<=m)set(l,r,y,idx<<1);
		if(r>m)set(l,r,y,idx<<1|1);
		pull(idx);
	}
	inline void add(const int &l,const int &r,const T &y,int idx = 1){
		if(l>r)return;
		if(l<=arr[idx].l and arr[idx].r<=r){
			arr[idx].mn += y;
			arr[idx].mx += y;
			arr[idx].sum += (arr[idx].r-arr[idx].l+1)*y;
			if(arr[idx].lz)arr[idx].lz+=y;
			else arr[idx].lz2 += y;
			return;
		}
		push(idx);
		int m = (arr[idx].l+arr[idx].r)>>1;
		if(l<=m)add(l,r,y,idx<<1);
		if(r>m)add(l,r,y,idx<<1|1);
		pull(idx);
	}
	inline node query(const int &l,const int &r,int idx = 1){
		if(l>r)return node();
		if(l<=arr[idx].l and arr[idx].r<=r){
			return arr[idx];
		}
		push(idx);
		int m = (arr[idx].l+arr[idx].r)>>1;
		node ans = node(),left = node(),right = node();
		if(l<=m)left = query(l,r,idx<<1);
		if(r>m)right = query(l,r,idx<<1|1);
		pull(ans,left,right);
		return ans;
	}
};
