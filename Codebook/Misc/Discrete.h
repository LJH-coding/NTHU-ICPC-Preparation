template<class T>
vector<int> Discrete(const vector<T>&v){
	vector<int>ans;
	vector<T>tmp(v);
	sort(begin(tmp),end(tmp));
	tmp.erase(unique(begin(tmp),end(tmp)),end(tmp));
	for(auto i:v)ans.push_back(lower_bound(begin(tmp),end(tmp),i)-tmp.begin()+1);
	return ans;
}
