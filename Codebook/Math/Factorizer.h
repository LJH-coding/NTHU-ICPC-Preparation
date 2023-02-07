template<class T>
vector<pair<T, int>> MergeFactors(const vector<pair<T, int>>& a, const vector<pair<T, int>>& b) {
	vector<pair<T, int>> c;
	int i = 0, j = 0;
	while(i < SZ(a) || j < SZ(b)) {
		if(i < SZ(a) && j < SZ(b) && a[i].F == b[j].F) {
			c.EB(a[i].F, a[i].S + b[j].S);
			++i, ++j;
			continue;
		}
		if(j == SZ(b) || (i < SZ(a) && a[i].F < b[j].F)) c.PB(a[i++]);
		else c.PB(b[j++]);
	}
	return c;
}
template<class T>
vector<pair<T, int>> RhoC(const T& n, const T& c) {
	if(n <= 1) return {};
	if(n % 2 == 0) return MergeFactors({{2, 1}}, RhoC(n / 2, c));
	if(is_prime_constexpr(n)) return {{n, 1}};
	T x = 2, saved = 2, p = 1, lam = 1;
	while(true) {
		x = (x * x % n + c) % n;
		T g = __gcd(((x - saved) + n) % n, n);
		if(g != 1) return MergeFactors(RhoC(g, c + 1), RhoC(n / g, c + 1));
		if(p == lam) {
			saved = x;
			p <<= 1;
			lam = 0;
		}
		lam += 1;
	}
	return {};
}
template<class T>
vector<pair<T, int>> Factorize(T n) {
	if(n <= 1) return {};
	return RhoC(n, T(1));
}
template<class T>
vector<T> BuildDivisorsFromFactors(const vector<pair<T, int>>& factors) {
	int total = 1;
	for(int i = 0; i < SZ(factors); ++i) total *= factors[i].second + 1;
	vector<T> divisors;
	divisors.reserve(total);
	divisors.PB(1);
	for(auto [p, cnt] : factors) {
		int sz = SZ(divisors);
		for(int i = 0; i < sz; ++i) {
			T cur = divisors[i];
			for(int j = 0; j < cnt; ++j) {
				cur *= p;
				divisors.PB(cur);
			}
		}
	}
	// sort(ALL(divisors));
	return divisors;
}
