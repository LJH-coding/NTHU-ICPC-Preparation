//Your task is to calculate the number of valid bracket sequences of length n when a prefix of the sequence is given.
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	if(n % 2 == 1) {
		cout << "0\n";
		return 0;
	}
	string s;
	cin >> s;
	int m = (int) s.size();
	int delta = 0;
	int left = 0;
	for(char& c : s) {
		delta += (c == '(' ? +1 : -1);
		left += (c == '(');
		if(delta < 0) {
			cout << "0\n";
			return 0;
		}
	}
	left = n / 2 - left;
	mint ans = C(n - m, left) - C(n - m, left + delta + 1);
	cout << ans << "\n";
	return 0;
}
