//0, 1, 2, 9, 44, 265, 1854, 14833, 133496, 1334961
#include <bits/stdc++.h>
 
#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
 
using namespace std;
 
#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
 
typedef uint64_t ull;
 
const int mod = 1e9 + 7, mxN = 1e6 + 1;
 
int n;
ull dp[mxN];
 
int main() {
	fastio;
	dp[1] = 0;
	dp[2] = 1;
	for(int i = 3; i < mxN; ++i)
		dp[i] = (i - 1) * (dp[i - 1] + dp[i - 2]) % mod;
	cin >> n;
	cout << dp[n] << "\n";
	
	return 0;
}
