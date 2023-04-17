long long AreaOfRectangles(vector<tuple<int,int,int,int>>v){
	vector<tuple<int,int,int,int>>tmp;
	int L = INT_MAX,R = INT_MIN;
	for(auto [x1,y1,x2,y2]:v){
		tmp.push_back({x1,y1+1,y2,1});
		tmp.push_back({x2,y1+1,y2,-1});
		R = max(R,y2);
		L = min(L,y1);
	}
	vector<long long>seg((R-L+1)<<2),tag((R-L+1)<<2);
	sort(tmp.begin(),tmp.end());
	function<void(int,int,int,int,int,int)>update = [&](int ql,int qr,int val,int l,int r,int idx){
		if(ql<=l and r<=qr){
			tag[idx]+=val;
			if(tag[idx])seg[idx] = r-l+1;
			else if(l==r)seg[idx] = 0;
			else seg[idx] = seg[idx<<1]+seg[idx<<1|1];
			return;
		}
		int m = (l+r)>>1;
		if(ql<=m)update(ql,qr,val,l,m,idx<<1);
		if(qr>m)update(ql,qr,val,m+1,r,idx<<1|1);
		if(tag[idx])seg[idx] = r-l+1;
		else seg[idx] = seg[idx<<1]+seg[idx<<1|1];
	};
	long long last_pos = 0,ans = 0;
	for(auto [pos,l,r,val]:tmp){
		ans+=(pos-last_pos)*seg[1];
		update(l,r,val,L,R,1);
		last_pos = pos;
	}
	return ans;
}
