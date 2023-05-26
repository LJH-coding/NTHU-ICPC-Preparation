//1, 2, 4, 8, 16, 32, 63, 125, 248, 492
#include <bits/stdc++.h>
using namespace std;
 
typedef uint64_t ull;
const int mod = 1e9 + 7;
 
struct Matrix {
	ull M[6][6];
	Matrix() {
		memset(M, 0, sizeof(M));
	}
	Matrix operator*(const Matrix& other) {
		Matrix ans;
		for(int i = 0; i < 6; ++i)
			for(int j = 0; j < 6; ++j)
				for(int k = 0; k < 6; ++k)
					ans.M[i][j] = (ans.M[i][j] + M[i][k] * other.M[k][j]) % mod;
		return ans;
	}
};
 
Matrix FastPower(Matrix a, ull b) {
	Matrix ans;
	for(int i = 0; i < 6; ++i)
		ans.M[i][i] = 1;
	while(b) {
		if(b & 1)
			ans = ans * a;
		a = a * a;
		b >>= 1;
	}
	return ans;
}
 
int main() {
	Matrix A;
	for(int i = 0; i < 6; ++i)
		A.M[0][i] = 1;
	for(int i = 1; i < 6; ++i)
		A.M[i][i - 1] = 1;
	ull n;
	cin >> n;
	cout << FastPower(A, n).M[0][0] << "\n";
	
	return 0;
}
 
