template<class T>struct fenwick_tree{
	int n;
	vector<T>arr;
	inline int lowbit(int x){
		return x&(-x);
	}
	fenwick_tree(int _n) : n(_n){
		arr.assign(n+5,0);
	}
	int query(int x){
		T ans = 0;
		for(int i = x;i>0;i-=lowbit(i)){
			ans+=arr[i];
		}
		return ans;
	}
	void update(int x,T y){
		for(int i = x;i<=n;i+=lowbit(i)){
			arr[i]+=y;
		}
	}
};
