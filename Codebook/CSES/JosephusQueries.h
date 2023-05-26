/*
Consider a game where there are n children (numbered 1,2,…,n) in a circle. During the game, every second child is removed from the circle, until there are no children left.

Your task is to process q queries of the form: "when there are n children, who is the kth child that will be removed?"
*/
#include <bits/stdc++.h>
using namespace std;
 
int f(int n, int k) {
	if(n == 1) {
		return 0;
	}
	if(k * 2 <= n) {
		return k * 2 - 1;
	}
	int pos = f(n - n / 2, k - n / 2);
	if(pos == 0) {
		return (n % 2 == 1 ? n - 1 : 0);
	}
	return (pos - n % 2) * 2;
}
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int tt;
	cin >> tt;
	while(tt--) {
		int n, k;
		cin >> n >> k;
		cout << f(n, k) + 1 << "\n";
	}
	return 0;
}
