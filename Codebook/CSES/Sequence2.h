//1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796
#include <bits/stdc++.h>
 
#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
 
using namespace std;
 
#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
 
typedef uint64_t ull;
 
ull FastPower(ull a, ull b, ull m) {
	a %= m;
	ull ans = 1;
	while(b) {
		if(b & 1)
			ans = ans * a % m;
		a = a * a % m;
		b >>= 1;
	}
	return ans;
}
 
const int mod = 1e9 + 7, mxN = 2e6 + 1;
 
ull n, f[mxN];
 
int main() {
	fastio;
	f[0] = 1;
	for(int i = 1; i < mxN; ++i)
		f[i] = f[i - 1] * i % mod;
	cin >> n;
	if(n & 1) {
		cout << "0\n";
		return 0;
	}
	n >>= 1;
	ull temp = FastPower(f[n], mod - 2, mod);
	cout << f[n << 1] * temp % mod * temp % mod * FastPower(n + 1, mod - 2, mod) % mod << "\n";
	
	return 0;
}
