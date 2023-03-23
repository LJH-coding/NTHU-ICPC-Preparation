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
