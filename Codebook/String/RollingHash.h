template<class T, int cnt>
struct rolling_hash {
    // {mul, mod}
	const vector<pair<int, int>> hash_pair = {{827167801, 999999937}, {998244353, 999999929}, {146672737, 922722049}, {204924373, 952311013}, {585761567, 955873937}, {484547929, 901981687}, {856009481, 987877511}, {852853249, 996724213}, {937381759, 994523539}, {116508269, 993179543}};
	
	int n;
	vector<int> power[10];
	array<vector<int>, cnt> pref;

	int substr(int k, int l, int r) {
		const auto& p = hash_pair[k];
		int res = pref[k][r];
		if(l > 0) res -= 1LL * pref[k][l - 1] * get_power(k, r - l + 1) % p.second;
		if(res < 0) res += p.second;
		return res;
	}

	int get_power(int a, int b) {
		const auto& p = hash_pair[a];
		while(power[a].size() <= b){
			if(power[a].empty()) power[a].push_back(1);
			else power[a].push_back(1ll * power[a].back() * p.first % p.second);
		}
		return power[a][b];
	}

    void add_char(char c) {
        for(int i = 0; i < n; ++i) {
            const auto& p = HASH_PAIRS[i];
            pref[i].push_back((1LL * (n == 0 ? 0 : pref[i].back()) * p.first + c) % p.second);
        }
        n += 1;
    }

	rolling_hash(T s = "") : n(s.size()) {
		for(int i = 0; i < cnt; ++i) {
			const auto& p = hash_pair[i];
			pref[i].resize(n);
			pref[i][0] = 1LL * s[0] % p.second;
			for(int j = 1; j < n; ++j) {
				pref[i][j] = (1LL * pref[i][j - 1] * p.first + s[j]) % p.second;
			}
		}
	}

	// Return hash values for [l, r]
	array<int, cnt> substr(int l, int r) {
		array<int, cnt> res{};
		for(int i = 0; i < cnt; ++i) {
			res[i] = substr(i, l, r);
		}
		return res;
	}
};
