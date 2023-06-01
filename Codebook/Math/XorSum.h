long long all_pair_xor_sum(vector<long long>v){
	int n = v.size();
	long long res = 0;
	for(int i = 0;i < 64;++i){
		int cnt0 = 0,cnt1 = 0;
		for(int j = 0; j < n; ++j){
			if(v[j] & 1)cnt1++;
			else cnt0++;
			v[j]>>=1;
		}
		res += (((1ll * cnt0 * cnt1) % mod) * ((1ll << i) % mod)) % mod;
		res %= mod;
	}
	return res;
}
