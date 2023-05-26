#include <bits/stdc++.h>
using namespace std;
 
template<int ALPHABET = 26, char MIN_CHAR = 'a'>
class suffix_automaton {
public:
	struct Node {
		int len;
		int suffLink;
		int go[ALPHABET] = {};
 
		Node() : Node(0, -1) {}
		Node(int a, int b) : len(a), suffLink(b) {}
	};
 
	suffix_automaton() : suffix_automaton(string(0, ' ')) {}
	suffix_automaton(const string& s) {
		SA.emplace_back();
		last = 0;
		for(char c : s) {
			add(c - MIN_CHAR);
		}
	}
 
	void add(int c) {
		int u = newNode();
		SA[u].len = SA[last].len + 1;
		int p = last;
		while(p != -1 && SA[p].go[c] == 0) {
			SA[p].go[c] = u;
			p = SA[p].suffLink;
		}
		if(p == -1) {
			SA[u].suffLink = 0;
			last = u;
			return;
		}
		int q = SA[p].go[c];
		if(SA[p].len + 1 == SA[q].len) {
			SA[u].suffLink = q;
			last = u;
			return;
		}
		int x = newNode();
		SA[x] = SA[q];
		SA[x].len = SA[p].len + 1;
		SA[q].suffLink = SA[u].suffLink = x;
		while(p != -1 && SA[p].go[c] == q) {
			SA[p].go[c] = x;
			p = SA[p].suffLink;
		}
		last = u;
		return;
	}
 
	bool match(const string& s) {
		int u = 0;
		for(char c : s) {
			int v = c - MIN_CHAR;
			if(SA[u].go[v] == 0) {
				return false;
			}
			u = SA[u].go[v];
		}
		return true;
	}
 
private:
	vector<Node> SA;
	int last;
 
	inline int newNode() {
		SA.emplace_back();
		return (int) SA.size() - 1;
	}
};
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	string s;
	cin >> s;
	suffix_automaton SA(s);
	int q;
	cin >> q;
	while(q--) {
		string t;
		cin >> t;
		cout << (SA.match(t) ? "YES" : "NO") << "\n";
	}
	return 0;
}