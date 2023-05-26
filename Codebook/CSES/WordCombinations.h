//You are given a string of length n and a dictionary containing k words. In how many ways can you create the string using the words?
#include <bits/stdc++.h>
 
#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
 
using namespace std;
 
#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
 
typedef int64_t ll;
 
const ll A = 912345693, B = 987654327, mxN = 5005, mod = 1e9 + 7;
 
int n;
string s;
ll h[mxN], p[mxN], dp[mxN];
vector<ll> num[mxN];
 
ll Get(int a, int b) {
	return ((h[b] - h[a - 1] * p[b - a + 1]) % B + B) % B;
}
 
int main() {
	fastio;
	p[0] = 1;
	for(int i = 1; i < mxN; ++i)
		p[i] = p[i - 1] * A % B;
	cin >> s >> n;
	s = " " + s;
	h[0] = 0;
	for(int i = 1; i <= s.size(); ++i)
		h[i] = (A * h[i - 1] + s[i]) % B;
	for(int i = 0; i < n; ++i) {
		string temp;
		cin >> temp;
		ll val = 0;
		for(char c : temp)
			val = (val * A + c) % B;
		num[temp.size()].push_back(val);
	}
	n = s.size() - 1;
	dp[0] = 1;
	for(int i = 0; i < n; ++i) {
		for(int j = 1; i + j <= n; ++j) {
			ll val = Get(i + 1, i + j);
			for(ll x : num[j])
				if(val == x)
					dp[i + j] = (dp[i + j] + dp[i]) % mod;
		}
	}
	cout << dp[n] << "\n";
	
	return 0;
}
