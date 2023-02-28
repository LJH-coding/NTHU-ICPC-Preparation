template<class T>
vector<int> Discrete(const vector<T>&v){
	vector<int>ans;
	vector<T>tmp(v);
	sort(all(tmp));
	tmp.erase(unique(all(tmp)),end(tmp));
	for(auto i:v)ans.pb(lower_bound(all(tmp),i)-tmp.begin()+1);
	return ans;
}
