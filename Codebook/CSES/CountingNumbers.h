//Your task is to count the number of integers between a and b where no two adjacent digits are the same.
#include <bits/extc++.h>
#include <bits/stdc++.h>
#pragma gcc optimize("ofast, unroll-loops, no-stack-protector, fast-math")
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define int long long
#define double long double
#define pb push_back
#define sz(x) (int)(x).size()
#define all(v) begin(v),end(v)
#define debug(x) cerr<<#x<<" = "<<x<<'\n'
#define LINE cout<<"\n-----------------\n"
#define endl '\n'
#define VI vector<int>
#define F first
#define S second
#define MP(a,b) make_pair(a,b)
#define rep(i,m,n) for(int i = m;i<=n;++i)
#define res(i,m,n) for(int i = m;i>=n;--i)
#define gcd(a,b) __gcd(a,b)
#define lcm(a,b) a*b/gcd(a,b)
#define Case() int _;cin>>_;for(int Case = 1;Case<=_;++Case)
#define pii pair<int,int>
#define lowbit(x) (x&(-x))
using namespace __gnu_cxx;
using namespace __gnu_pbds;
using namespace std;
template <typename K, typename cmp = less<K>, typename T = thin_heap_tag> using _heap = __gnu_pbds::priority_queue<K, cmp, T>;
template <typename K, typename M = null_type> using _hash = gp_hash_table<K, M>;
const int N = 1e6+5,L = 20,mod = 1e9+7,inf = 2e9+5;
const double eps = 1e-7,pi = acos(-1);
mt19937 mt(std::chrono::system_clock::now().time_since_epoch().count());
int cnt(int x){
	if(x<0)return 0;
	string s = std::to_string(x);
	reverse(all(s));
	int n = s.size(),ans = 0;
	int dp[n][2][10] = {};
	for(int i = 0;i<10;++i){
		dp[0][(i>(s[0]-'0'))][i]++;
	}
	for(int i = 1;i<n;++i){
		for(int j = 0;j<2;++j){
			for(int last = 0;last<10;++last){
				for(int add = 0;add<10;++add){
					if(add==last)continue;
					bool flag = (add>(s[i]-'0')) or (add==(s[i]-'0') and j);
					dp[i][flag][add]+=dp[i-1][j][last];
				}
			}
		}
	}
	for(int i = 0;i<n-1;++i){
		for(int j = 0;j<2;++j){
			for(int k = 1;k<10;++k){
				ans+=dp[i][j][k];
			}
		}
	}
	for(int i = 1;i<10;++i){
		ans+=dp[n-1][0][i];
	}
	return ans+1;
}
void solve(){
	int a,b;
	cin>>a>>b;
	cout<<cnt(b)-cnt(a-1)<<endl;
}
signed main(){
	IOS;
	solve();
}
