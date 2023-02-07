template<class T>struct treap{
	struct node{
		int sz,pri,lz,sum,mx;
		T val;
		node *l,*r;
		node(T _val){
			val = mx = sum = _val;
			lz = 0,sz = 1,pri = rand();
			l = r = NULL;
		}
	};
	node *root = NULL;
	int size(node *a){
		return a?a->sz:0;
	}
	void push(node *a){
		if(!a->lz)return;
		swap(a->l,a->r);
		if(a->l)a->l->lz ^= 1;
		if(a->r)a->r->lz ^= 1;
		a->lz = 0;
	}
	void pull(node *a){
		a->sz = 1,a->sum = a->mx = a->val;
		if(a->l){
			a->sz+=a->l->sz;
			a->sum+=a->l->sum;
			a->mx = max(a->mx,a->l->mx);
		}
		if(a->r){
			a->sz+=a->r->sz;
			a->sum+=a->r->sum;
			a->mx = max(a->mx,a->r->mx);
		}
	}
	node *merge(node *a,node *b){
		if(!a or !b)return a?a:b;
		if(a->pri > b->pri){
			push(a);
			a->r = merge(a->r,b);
			pull(a);
			return a;
		}
		else{
			push(b);
			b->l = merge(a,b->l);
			pull(b);
			return b;
		}
	}
	void split_kth(node *t,int k,node *&a,node *&b){
		if(!t){a = b = NULL;return;};
		push(t);
		if(size(t->l) + 1<=k){
			a = t;
			split_kth(t->r,k-size(t->l)-1,a->r,b);
			pull(a);
		}
		else{
			b = t;
			split_kth(t->l,k,a,b->l);
			pull(b);
		}
	}
	void split_key(node *t,T k,node *&a,node *&b){
		if(!t){a = b = NULL;return;};
		push(t);
		if(k<=t->val){
			b = t;
			split_key(t->l,k,a,b->l);
			pull(b);
		}
		else{
			a = t;
			split_key(t->r,k,a->r,b);
			pull(a);
		}
	}
	void insert(node *&t,T k){
		node *a,*b;
		split_key(t,k,a,b);
		t = merge(a,merge(new node(k),b));
	}void insert(T k){
		insert(root,k);
	}
	bool erase(node *&t,T k){
		if(!t)return 0;
		if(t->val==k){
			node *tmp = t;
			t = merge(t->l,t->r);
			delete tmp;
			return 1;
		}
		return erase(k<(t->val)?t->l:t->r,k);
	}bool erase(T k){
		return erase(root,k);
	}
	bool count(node *t,T k){
		if(!t)return 0;
		if(t->val==k)return 1;
		return count(k<(t->val)?t->l:t->r,k);
	}bool count(T k){
		return count(root,k);
	}
	node *find_by_order(node *&t,int k){
		node *a,*b,*c;
		split_kth(t,k,a,c);
		split_kth(a,k-1,a,b);
		t = merge(a,merge(b,c));
		return b;
	}node *find_by_order(int k){
		return find_by_order(root,k);
	}
	int order_of_key(node *&t,T k){
		node *a,*b;
		split_key(t,k,a,b);
		int ans = size(a);
		t = merge(a,b);
		return ans;
	}int order_of_key(T k){
		return order_of_key(root,k);
	}
	void reverse(node *&t,int l,int r){
		node *a,*b,*c;
		split_kth(t,l-1,a,b);
		split_kth(b,r-l+1,b,c);
		b->lz^=1;
		t = merge(a,merge(b,c));
	}void reverse(int l,int r){
		reverse(root,l,r);
	}
	node query(node *&t,int l,int r){
		node *a,*b,*c;
		split_kth(t,l-1,a,b);
		split_kth(b,r-l+1,b,c);
		push(b);
		node ans = b;
		t = merge(a,merge(b,c));
		return ans;
	}node query(int l,int r){
		return query(root,l,r);
	}
	void print(node *now){
		if(!now)return;
		push(now);
		print(now->l);
		cout<<now->val<<' ';
		print(now->r);
	}void print(){
		print(root);
	}
	void push_back(T k){
		root = merge(root,new node(k));
	}
	void push_front(T k){
		root = merge(new node(k),root);
	}
};
