/*
There are n heaps of coins and two players who move alternately. On each move, a player selects some of the nonempty heaps and removes one coin from each heap. The player who removes the last coin wins the game.

Your task is to find out who wins if both players play optimally.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int tt;
	cin >> tt;
	while(tt--) {
		int n;
		cin >> n;
		bool b = false;
		for(int i = 0; i < n; ++i) {
			int x;
			cin >> x;
			b = (b || x % 2);
		}
		cout << (b ? "first" : "second") << "\n";
	}
	return 0;
}
