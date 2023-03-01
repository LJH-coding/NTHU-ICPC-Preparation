template<class T>struct dynamic_segment_tree{
	struct node{
		node *l = NULL,*r = NULL;
		T sum;
		node(T k = 0): sum(k){}
		node(node *p){*this = *p;}
		~node(){
			for(auto &i:{l,r})
				if(i)delete i;
		}
		void pull(){
			sum = 0;
			for(auto i:{l,r})
				if(i)sum+=i->sum;
		}
	}*root = NULL;
	int n;
	dynamic_segment_tree(int _n): n(_n){}
	dynamic_segment_tree(int _n,const dynamic_segment_tree<T>&tmp): n(_n){root = new node(tmp.root);}
	void update(node *&t,int pos,T k,int l,int r){
		if(l==r)return t = new node(k),void();
		if(!t)t = new node();
		int m = (l+r)>>1;
		t = new node(t);
		if(pos<=m)update(t->l,pos,k,l,m);
		else update(t->r,pos,k,m+1,r);
		t->pull();
	}void update(int pos,T k){update(root,pos,k,1,n);}
	T query(node *t,int ql,int qr,int l,int r){
		if(!t)return 0;
		if(ql<=l and r<=qr)return t->sum;
		int m = (l+r)>>1;
		T ans = 0;
		if(ql<=m)ans+=query(t->l,ql,qr,l,m);
		if(qr>m)ans+=query(t->r,ql,qr,m+1,r);
		return ans;
	}T query(int ql,int qr){return query(root,ql,qr,1,n);}
};
