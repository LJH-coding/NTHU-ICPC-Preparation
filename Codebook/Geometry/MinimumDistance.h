template<class T>
T MinimumDistance(vector<Point<T>>&p,int l = -1,int r = -1){
	if(l==-1 and r==-1){
		sort(p.begin(),p.end(),[](Point<T> a,Point<T> b){
			if(a.x!=b.x)return a.x<b.x;
			return a.y<b.y;
		});
		p.erase(unique(p.begin(),p.end()),p.end());
		return MinimumDistance(p,0,p.size()-1);
	}
	if(l==r)return numeric_limits<T>::max();
	int m = (l+r)>>1,mid_pos = p[m].x;
	T ans = min(MinimumDistance(p,l,m),MinimumDistance(p,m+1,r));
	vector<Point<T>>tmp((r-l+1),Point<T>(0,0));
	merge(p.begin()+l,p.begin()+m+1, p.begin()+m+1,p.begin()+r+1, tmp.begin(), [](Point<T> a,Point<T> b){return a.y<b.y;});
	for(int i = l;i<=r;++i)p[i] = tmp[i-l];
	tmp.clear();
	for(int i = l;i<=r;++i){
		if((p[i].x-mid_pos)*(p[i].x-mid_pos)<ans){
			tmp.push_back(p[i]);
		}
	}
	int n = tmp.size();
	for(int i = 0;i<n;++i){
		for(int j = i+1;j<n;++j){
			ans = min(ans,abs2(tmp[i]-tmp[j]));
			if(((tmp[i].y-tmp[j].y)*(tmp[i].y-tmp[j].y))>ans){
				break;
			}
		}
	}
	return ans;
}
