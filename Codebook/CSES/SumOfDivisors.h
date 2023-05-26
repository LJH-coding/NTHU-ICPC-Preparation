/*
Let σ(n) denote the sum of divisors of an integer n. For example, σ(12)=1+2+3+4+6+12=28.

Your task is to calculate the sum ∑(i = 1, n) σ(i) modulo 10^9+7.
*/
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 1e9 + 7;
constexpr long long Pow(long long x, long long n, int m) {
	if(m == 1) return 0;
	unsigned int _m = (unsigned int)(m);
	unsigned long long r = 1;
	x %= m;
	if(x < 0) x += m;
	unsigned long long y = x;
	while(n) {
		if(n & 1) r = (r * y) % _m;
		y = (y * y) % _m;
		n >>= 1;
	}
	return r;
}
signed main(){
	int n;
	cin>>n;
	int ans = 0;
	for(int l = 1, r = n / (n / l); l <= n; l = r + 1){
		r = n / (n / l);
		ans += (((((((l + r) % mod) * ((r - l + 1) % mod)) % mod) * Pow(2, mod - 2, mod)) % mod) * ((n / l) % mod)) % mod;
		ans %= mod;
	}
	cout<<ans<<endl;
}
