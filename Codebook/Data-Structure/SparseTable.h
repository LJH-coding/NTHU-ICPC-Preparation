template<class T,T (*op)(T, T)>struct sparse_table {
	int n;
	vector<vector<T>> mat;
	sparse_table(): n(0){}
	sparse_table(const vector<T> &v) {
		n = (int)(v.size());
		mat.resize(30);
		mat[0] = v;
		for(int i = 1; (1 << i) <= n; ++i) {
			mat[i].resize(n - (1 << i) + 1);
			for(int j = 0; j < n - (1 << i) + 1; ++j) {
				mat[i][j] = op(mat[i - 1][j], mat[i - 1][j + (1 << (i - 1))]);
			}
		}
	}
	T query(int ql, int qr) {
		int k = __lg(qr - ql + 1);
		return op(mat[k][ql], mat[k][qr - (1 << k) + 1]);
	}
};
