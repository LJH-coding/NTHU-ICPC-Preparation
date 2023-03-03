
template<class T>struct dynamic_segment_tree{
	struct node{
		node *l = NULL,*r = NULL;
		T sum;
		node(T k = 0): sum(k){}
		node(node *p){if(p)*this = *p;}
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
	dynamic_segment_tree(){}
	dynamic_segment_tree(const dynamic_segment_tree<T>&tmp){root = new node(tmp.root);}
	void update(node *&t,int pos,T k,int l,int r){
		if(!t)t = new node();
		if(l==r)return t = new node(k),void();
		int m = (l+r)>>1;
		t = new node(t);
		if(pos<=m)update(t->l,pos,k,l,m);
		else update(t->r,pos,k,m+1,r);
		t->pull();
	}void update(int pos,T k,int l = -1e9,int r = 1e9){update(root,pos,k,l,r);}
	T query(node *&t,int ql,int qr,int l,int r){
		if(!t)return 0;
		if(ql<=l and r<=qr)return t->sum;
		int m = (l+r)>>1;
		T ans = 0;
		if(ql<=m)ans+=query(t->l,ql,qr,l,m);
		if(qr>m)ans+=query(t->r,ql,qr,m+1,r);
		return ans;
	}T query(int ql,int qr,int l = -1e9,int r = 1e9){return query(root,ql,qr,l,r);}
};
