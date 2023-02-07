template<class T>struct segment_tree{
	int n;
	struct node{
		int l,r;
		T lz,lz2;
		T sum,mx,mn;
		node(){
			l = r = lz  = lz2 = sum = mx = mn = 0;
		}
		friend bool operator ==(node a,node b){
			return (a.l==b.l and a.r==b.r);
		}
	};
	vector<node>arr;
	segment_tree(int _n) : n(_n) {
		arr.assign(n<<2,node());
	}
	void pull(node &ans,node left,node right){
		if(left==node()){
			ans = right;
			return;
		}
		if(right==node()){
			ans = left;
			return;
		}
		ans.mx = max(left.mx,right.mx);
		ans.mn = min(left.mn,right.mn);
		ans.sum = left.sum+right.sum;
		ans.l = left.l,ans.r = right.r;
	}void pull(int idx){
		pull(arr[idx],arr[idx<<1],arr[idx<<1|1]);
	}
	void push(int idx){
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
		}
		else if(arr[idx].lz2){
			arr[idx<<1].mn += arr[idx].lz;
			arr[idx<<1].mx += arr[idx].lz;
			arr[idx<<1].sum+=(m-arr[idx].l+1)*arr[idx].lz2;
			if(arr[idx<<1].lz==0)arr[idx<<1].lz2+=arr[idx].lz2;
			else{
				arr[idx<<1].lz+=arr[idx].lz2;
				arr[idx<<1].lz2 = 0;
			}
			arr[idx<<1|1].mn += arr[idx].lz;
			arr[idx<<1|1].mx += arr[idx].lz;
			arr[idx<<1|1].sum+=(arr[idx].r-m)*arr[idx].lz2;
			if(arr[idx<<1|1].lz==0)arr[idx<<1|1].lz2+=arr[idx].lz2;
			else{
				arr[idx<<1|1].lz+=arr[idx].lz2;
				arr[idx<<1|1].lz2 = 0;
			}
			arr[idx].lz2 = 0;
		}
	}
	void build(const vector<T>&v,int l,int r,int idx){
		if(l==r){
			arr[idx].sum = arr[idx].mn = arr[idx].mx = v[l];
			arr[idx].l = arr[idx].r = l;
			arr[idx].lz = arr[idx].lz2 = 0;
			return;
		}
		int m = (l+r)>>1;
		build(v,l,m,idx<<1);
		build(v,m+1,r,idx<<1|1);
		pull(idx);
	}void build(const vector<T>&v,int r){
		build(v,1,r,1);
	}
	void set(int l,int r,T y,int idx = 1){
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
	void add(int l,int r,T y,int idx = 1){
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
	node query(int l,int r,int idx = 1){
		if(l<=arr[idx].l and arr[idx].r<=r){
			return arr[idx];
		}
		push(idx);
		int m = (arr[idx].l+arr[idx].r)>>1;
		node ans,left,right;
		if(l<=m)left = query(l,r,idx<<1);
		if(r>m)right = query(l,r,idx<<1|1);
		pull(ans,left,right);
		return ans;
	}
};
