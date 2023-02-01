struct qry{
	int ql,qr,id;
};
template<class T>struct Mo{
	int n,m;
	vector<pii>ans;
	Mo(int _n,int _m): n(_n),m(_m){
		ans.resize(m);
	}
	void solve(vector<T>&v,vector<qry>&q){
		int l = 0,r = -1;
		vector<int>cnt,cntcnt;
		cnt.resize(n+5);
		cntcnt.resize(n+5);
		int mx = 0;
		function<void(int)>add = [&](int pos){
			cntcnt[cnt[v[pos]]]--;
			cnt[v[pos]]++;
			cntcnt[cnt[v[pos]]]++;
			mx = max(mx,cnt[v[pos]]);
		};
		function<void(int)>sub = [&](int pos){
			if(!--cntcnt[cnt[v[pos]]] and cnt[v[pos]]==mx)mx--;
			cnt[v[pos]]--;
			cntcnt[cnt[v[pos]]]++;
			mx = max(mx,cnt[v[pos]]);
		};
		sort(all(q),[&](qry a,qry b){
			static int B = n/max((T)sqrt(m),(T)1);
			if(a.ql/B!=b.ql/B)
				return a.ql/B<b.ql/B;
			return a.qr/B<b.qr/B;
		});
		for(auto [ql,qr,id]:q){
			while(l>ql)add(--l);
			while(r<qr)add(++r);
			while(l<ql)sub(l++);
			while(r>qr)sub(r--);
			ans[id] = {mx,cntcnt[mx]};
		}
	}
};
