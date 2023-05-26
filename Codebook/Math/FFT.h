// Fast-Fourier-Transform
using cd = complex<double>;
const double PI = acos(-1); 

void FFT(vector<cd>& a, bool inv) {
	int n = (int) a.size();
	for(int i = 1, j = 0; i < n; ++i) {
		int bit = n >> 1;
		for(; j & bit; bit >>= 1) {
			j ^= bit;
		}
		j ^= bit;
		if(i < j) {
			swap(a[i], a[j]);
		}
	}
	for(int len = 2; len <= n; len <<= 1) {
		const double ang = 2 * PI / len * (inv ? -1 : +1);
		cd rot(cos(ang), sin(ang));
		for(int i = 0; i < n; i += len) {
			cd w(1);
			for(int j = 0; j < len / 2; ++j) {
				cd u = a[i + j], v = a[i + j + len / 2] * w;
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
				w *= rot;
			}
		}
	}
	if(inv) {
		for(auto& x : a) {
			x /= n;
		}
	}
}

vector<int> multiply(const vector<int>& a, const vector<int>& b) {
	vector<cd> fa(a.begin(), a.end());
	vector<cd> fb(b.begin(), b.end());
	int n = 1;
	while(n < (int) a.size() + (int) b.size() - 1) {
		n <<= 1;
	}
	fa.resize(n);
	fb.resize(n);
	FFT(fa, false);
	FFT(fb, false);
	for(int i = 0; i < n; ++i) {
		fa[i] *= fb[i];
	}
	FFT(fa, true);
	vector<int> c(a.size() + b.size() - 1);
	for(int i = 0; i < (int) c.size(); ++i) {
		c[i] = round(fa[i].real());
	}
	return c;
}
