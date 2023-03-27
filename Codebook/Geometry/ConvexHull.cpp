template<class T>
vector<Point<T>> ConvexHull(vector<Point<T>> v){
	sort(begin(v),end(v),[&](Point<T> &a,Point<T> &b){
		if(a.x!=b.x)return a.x<b.x;
		return a.y<b.y;
	});
	vector<Point<T>>ans;
	int t = 1;
	auto add = [&](Point<T> &p){
		while(ans.size() > t and ((p - ans[ans.size() - 2])^(ans.back() - ans[ans.size() - 2])) > 0)
			ans.pop_back();
		ans.push_back(p);
	};
	for(int i = 0; i < v.size(); ++i) add(v[i]);
	t = ans.size();
	for(int i = (int)(v.size())-2; i >= 0; --i) add(v[i]);
	if(v.size() > 1) ans.pop_back();
	return ans;
}
