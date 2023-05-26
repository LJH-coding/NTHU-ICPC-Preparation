//Your task is to count the number of ways you can fill an n×m grid using 1×2 and 2×1 tiles.
int dp[1005][1<<10] = {};
vector<pii>v;
void solve(){
	int n,m;
	cin>>n>>m;
	for(int a = 0;a<(1<<n);++a){
		for(int b = 0;b<(1<<n);++b){
			bool flag = 1;
			for(int i = 0;i<n;++i){
				if(a&(1<<i) and b&(1<<i)){
					if(i==n-1 or !(a&(1<<(i+1))) or !(b&(1<<(i+1))))flag = 0;
					else{
						i++;
						continue;
					}
				}
				if(!(a&(1<<i)) and !(b&(1<<i)))flag = 0;
			}
			if(flag)v.pb({a,b});
		}
	};
	dp[0][(1<<n)-1] = 1;
	for(int i = 1;i<=m;++i){
		for(auto j:v)dp[i][j.S] = (1ll*dp[i-1][j.F]+dp[i][j.S])%mod;
	}
	cout<<dp[m][(1<<n)-1]<<endl;
}
signed main(){
	IOS;
	solve();
}
