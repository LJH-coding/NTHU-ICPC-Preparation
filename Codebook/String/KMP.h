template<class T>
vector<int> KMP(const vector<T>& a) {
	int n = (int) a.size();
	vector<int> k(n);
	for(int i = 1; i < n; ++i) {
		int j = k[i - 1];
		while(j > 0 && a[i] != a[j]) {
			j = k[j - 1];
		}
		j += (a[i] == a[j]);
		k[i] = j;
	}
	return k;
}

vector<int> KMP(const std::string& s) {
	return KMP(vector<int>(s.begin(), s.end()));
}

