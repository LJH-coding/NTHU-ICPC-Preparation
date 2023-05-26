/*
There is a list of n numbers and two players who move alternately. On each move, a player removes either the first or last number from the list, and their score increases by that number. Both players try to maximize their scores.

What is the maximum possible score for the first player when both players play optimally?
*/
#include <bits/stdc++.h>
using namespace std;
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	vector<long long> a(n), pref(n + 1);
	for(int i = 0; i < n; ++i) {
		cin >> a[i];
		pref[i + 1] = pref[i] + a[i];
	}
	vector<vector<long long>> dp(n, vector<long long>(n));
	for(int i = 0; i < n; ++i) {
		dp[i][i] = a[i];
	}
	for(int len = 2; len <= n; ++len) {
		for(int i = 0; i + len - 1 < n; ++i) {
			int j = i + len - 1;
			dp[i][j] = pref[j + 1] - pref[i] - min(dp[i + 1][j], dp[i][j - 1]);
		}
	}
	cout << dp[0][n - 1] << "\n";
	return 0;
}
