int DiscreteLog(int s, int x, int y, int m) {
	constexpr int K = 0;
	hash_map<int, int> p;
	int b = 1;
	for(int i = 0; i < K; ++i) {
		p[y] = i;
		y = 1LL * y * x % m;
		b = 1LL * b * x % m;
	}
	for(int i = 0; i < m + 10; i += K) {
		s = 1LL * s * b % m;
		if(p.find(s) != p.end()) return i + K - p[s];
	}
	return -1;
}
int DiscreteLog(int x, int y, int m) {
	if(m == 1) return 0;
	int s = 1;
	for(int i = 0; i < 100; ++i) {
		if(s == y) return i;
		s = 1LL * s * x % m;
	}
	if(s == y) return 100;
	int p = 100 + DiscreteLog(s, x, y, m);
	return (pow_mod(x, p, m) != y ? -1 : p);
}
