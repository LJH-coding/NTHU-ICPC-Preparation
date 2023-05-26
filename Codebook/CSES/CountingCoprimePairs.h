/*
Given a list of n positive integers, your task is to count the number of pairs of integers that are coprime (i.e., their greatest common divisor is one).
*/
#include <bits/stdc++.h>
using namespace std;
 
const int N = 1e6 + 5;
 
int main(int argc, char* argv[]) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	vector<bool> isprime(N + 1, true);
	isprime[0] = isprime[1] = false;
	vector<int> prime;
	vector<int> mu(N + 1);
	mu[1] = 1;
	for(int i = 2; i <= N; ++i) {
		if(isprime[i]) {
			mu[i] = -1;
			prime.push_back(i);
		}
		for(int j = 0; j < (int) prime.size() && i * prime[j] <= N; ++j) {
			isprime[i * prime[j]] = false;
			mu[i * prime[j]] = mu[i] * mu[prime[j]];
			if(i % prime[j] == 0) {
				mu[i * prime[j]] = 0;
				break;
			}
		}
	}
	int n;
	cin >> n;
	vector<int> cnt(N + 1);
	for(int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		cnt[x] += 1;
	}
	long long ans = 0;
	for(int i = 1; i <= N; ++i) {
		long long s = 0;
		for(int j = i; j <= N; j += i) {
			s += cnt[j];
		}
		ans += 1LL * mu[i] * s * (s - 1) / 2;
	}
	cout << ans << "\n";
	return 0;
}


