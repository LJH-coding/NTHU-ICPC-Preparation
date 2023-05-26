//Count the number of distinct substrings that appear in a string.
//abaa => 8 : Explanation: the substrings are a, b, aa, ab, ba, aba, baa and abaa. 
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
using namespace __gnu_cxx;
using namespace __gnu_pbds;
using namespace std;
template <typename K, typename cmp = less<K>, typename T = thin_heap_tag> using _heap = __gnu_pbds::priority_queue<K, cmp, T>;
template <typename K, typename M = null_type> using _hash = gp_hash_table<K, M>;
const int N = 1e6+5,L = 20,mod = 1e9+7;
const long long inf = 2e18+5;
const double eps = 1e-7,pi = acos(-1);
mt19937 mt(std::chrono::system_clock::now().time_since_epoch().count());
struct suffix_array{
	int n;
	vector<int>SA,Rank,LCP;
	void counting_sort(vector<int>&v,auto getkey){
		int n = 0;
		for(auto i:v)n = max(n,getkey(i)+1);
		vector<int>bucket(n),ans(v.size());
		for(auto i:v)++bucket[getkey(i)];
		partial_sum(begin(bucket),end(bucket),begin(bucket));
		for(auto ite = v.rbegin();ite!=v.rend();++ite)ans[--bucket[getkey(*ite)]] = move(*ite);
		v.swap(ans);
		return;
	}
	suffix_array(string s):n(s.size()){
		SA.resize(n),Rank.resize(n),LCP.resize(n);
		for(int i = 0;i<n;++i)SA[i] = i;
		sort(SA.begin(),SA.end(),[&](int a,int b){
			return s[a]<s[b];
		});
		for(int i = 0;i<n;++i){
			Rank[SA[i]] = (i?Rank[SA[i-1]]+(s[SA[i]]!=s[SA[i-1]]):SA[0]);
		}
		for(int k = 0;(1<<k)<=n;++k){
			vector<int>idx;
			for(int i = n-(1<<k);i<n;++i)idx.push_back(i);
			for(auto i:SA)if(i>=(1<<k))idx.push_back(i-(1<<k));
			counting_sort(idx,[&](int a){return Rank[a];});
			SA.swap(idx);
			vector<int>new_rank(n);
			new_rank[SA[0]] = 0;
			for(int i = 1;i<n;++i){
				auto cmp = [&](int a,int b){
					return Rank[a]!=Rank[b] or a+(1<<k)>=n or Rank[a+(1<<k)]!=Rank[b+(1<<k)];
				};
				new_rank[SA[i]] = new_rank[SA[i-1]]+cmp(SA[i-1],SA[i]);
			}
			Rank.swap(new_rank);
		}
		for(int i = 0,k = 0;i<n;++i){
			if(Rank[i]==0)continue;
			if(k)--k;
			while(i+k<n and SA[Rank[i]-1]+k<n and s[i+k]==s[SA[Rank[i]-1]+k])++k;
			LCP[Rank[i]] = k;
		}
	}
};
void solve(){
	string s;
	getline(cin,s);
	suffix_array sa(s);
	int n = s.size();
	int ans = n*(n+1)/2;
	for(int i = 1;i<n;++i)ans-=sa.LCP[i];
	cout<<ans<<endl;
}
signed main(){
	IOS;
	solve();
}
