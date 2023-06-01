template<class S, S (*node_pull)(S, S), S (*node_init)(), const long long L, const long long R>struct dynamic_segment_tree{
	struct node{
		node *l = NULL,*r = NULL;
		S seg;
		node(S s = node_init()): seg(s) {}
		node(node *p) {if(p)*this = *p;}
		~node(){
			for(auto &i:{l,r})
				if(i)delete i;
		}
		void pull(){
			if(!l)seg = r->seg;
			else if(!r)seg = l->seg;
			else seg = node_pull(l->seg, r->seg);
		}
	}*root = NULL;
	dynamic_segment_tree(){}
	dynamic_segment_tree(const dynamic_segment_tree<S, node_pull, node_init, L, R>&tmp){root = new node(tmp.root);}
	void update(node *&t,int pos, S k,int l,int r){
		if(!t)t = new node();
		if(l==r){
			return t = new node(node_pull(t->seg, k)),void();
		}
		int m = (l+r)>>1;
		t = new node(t);
		if(pos<=m)update(t->l,pos,k,l,m);
		else update(t->r,pos,k,m+1,r);
		t->pull();
	}void update(int pos, S k){update(root,pos,k, L, R);}
	S query(node *&t,int ql,int qr,int l,int r){
		if(!t)return 0;
		if(ql<=l and r<=qr)return t->seg;
		int m = (l+r)>>1;
		S lhs = node_init(), rhs = node_init();
		if(ql<=m)lhs =  query(t->l,ql,qr,l,m);
		if(qr>m)rhs = query(t->r,ql,qr,m+1,r);
		return node_pull(lhs, rhs);
	}S query(int ql,int qr){return query(root, ql, qr, L, R);}
};
