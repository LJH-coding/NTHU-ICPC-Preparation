struct Matrix {
    vector<vector<int>> v;
    int n, m;
    Matrix(vector<vector<int>> tmp) {
        v = tmp;
        n = tmp.size();
        m = tmp[0].size();
    }
    friend Matrix operator *(const Matrix &a, const Matrix &b) {
        Matrix res(vector<vector<int>>(a.n, vector<int>(b.m)));
        assert(a.m == b.n);
        for(int i = 0; i < a.n; ++i) {
            for(int j = 0; j < b.m; ++j) {
                for(int k = 0; k < a.m; ++k) {
                    res.v[i][j] = (1ll * res.v[i][j] + 1ll * a.v[i][k] * b.v[k][j]) % mod;
                    res.v[i][j] += mod;
                    res.v[i][j] %= mod;
                }
            }
        }
        return res;
    }
    friend Matrix operator %(Matrix a, const int mod) {
        for(int i = 0; i < a.n; ++i) {
            for(int j = 0; j < a.m; ++j) {
                a.v[i][j] %= mod;
                a.v[i][j] += mod;
                a.v[i][j] %= mod;
            }
        }
        return a;
    }
    void Pow(long long k, int mod) {
        assert(n == m);
        Matrix res(vector<vector<int>>(n, vector<int>(m)));
        for(int i = 0; i < n; ++i) res.v[i][i] = 1;
        (*this) = (*this) % mod;
        while(k) {
            if(k & 1) {
                res = res * (*this);
                res = res % mod;
            }
            k >>= 1;
            *this = (*this) * (*this);
            *this = (*this) % mod;
        }
        (*this) = res;
    }
};
