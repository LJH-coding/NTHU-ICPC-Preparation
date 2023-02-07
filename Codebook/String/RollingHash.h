template<class T>struct rolling_hash{
    int p = 107,q = 1e9+7;
    vector<int>p_table,hash;
    void build(T v){
        hash.resize(v.size()),p_table.resize(v.size());
        p_table[0] = 1,hash[0] = (int)v[0];
        for(int i = 1;i<v.size();++i){
            p_table[i] = (1ll*p_table[i-1]*p)%q;
            hash[i] = (1ll*hash[i-1]*p+(int)v[i])%q;
        }
    }
    int query(int l,int r){
        if(l==0)return hash[r];
        int ans = (hash[r]-(1ll*hash[l-1]*p_table[r-l+1]))%q;
        ans = (ans+q)%q;
        return ans;
    }
};
