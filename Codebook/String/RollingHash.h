template<class T,const int hash_cnt>struct rolling_hash{
	static constexpr const pair<int, int> hash_value[] = {{827167801, 999999937},
									  {998244353, 999999929},
									  {146672737, 922722049},
									  {204924373, 952311013},
									  {585761567, 955873937},
									  {484547929, 901981687},
									  {856009481, 987877511},
									  {852853249, 996724213},
									  {937381759, 994523539},
									  {116508269, 993179543}};
    vector<vector<int>>p_table,hash;
    void build(T v){
		p_table.resize(hash_cnt),hash.resize(hash_cnt);
		for(int i = 0;i<hash_cnt;++i){
			hash[i].resize(v.size()),p_table[i].resize(v.size());
			p_table[i][0] = 1,hash[i][0] = (int)v[0];
			int p = hash_value[i].first,q = hash_value[i].second;
			for(int j = 1;j<v.size();++j){
				p_table[i][j] = (1ll*p_table[i][j-1]*p)%q;
				hash[i][j] = (1ll*hash[i][j-1]*p+(int)v[j])%q;
			}
		}
    }
    array<int,hash_cnt> query(int l,int r){
		array<int,hash_cnt>ans;
        if(l==0){
			for(int i = 0;i<hash_cnt;++i){
				ans[i] = hash[i][r];
			}
			return ans;
		}
		for(int i = 0;i<hash_cnt;++i){
			int p = hash_value[i].first,q = hash_value[i].second;
			int x = (hash[i][r]-(1ll*hash[i][l-1]*p_table[i][r-l+1]))%q;
			x = (x+q)%q;
			ans[i] = x;
		}
        return ans;
    }
};
