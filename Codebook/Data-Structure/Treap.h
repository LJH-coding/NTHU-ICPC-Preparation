mt19937 mt(hash<string>()("Treap"));
template<class T>struct Treap{
	struct node{
		node *l = NULL,*r = NULL;
		T key;
		int pri = mt(),sz = 1;
		bool rev = 0;
		node(T x):key(x){}
		~node(){
			for(auto &i:{l,r})
				delete i;
		}
		void push(){
			if(!rev)return;
			swap(l,r);
			for(auto &i:{l,r})
				if(i)i->rev^=1;
			rev = 0;
		}
		void pull(){
			sz = 1;
			for(auto i:{l,r})
				if(i)sz+=i->sz;
		}
	};
	node *root = NULL;
	int size(node *a){
		return a?a->sz:0;
	}
	node *merge(node *a,node *b){
		if(!a or !b)return a?:b;
		if(a->pri>b->pri){
			a->push();
			a->r = merge(a->r,b);
			a->pull();
			return a;
		}
		else{
			b->push();
			b->l = merge(a,b->l);
			b->pull();
			return b;
		}
	}
	void split(node *t,int k,node *&a,node *&b){
		if(!t){a = b = NULL;return;}
		t->push();
		if(size(t->l)+1<=k){
			a = t;
			split(t->r,k-size(t->l)-1,a->r,b);
			a->pull();
		}
		else{
			b = t;
			split(t->l,k,a,b->l);
			b->pull();
		}
	}
	void split_by_key(node *t,T k,node *&a,node *&b){
		if(!t){a = b = NULL;return;}
		t->push();
		if(t->key<=k){
			a = t;
			split_by_key(t->r,k,a->r,b);
			a->pull();
		}
		else{
			b = t;
			split_by_key(t->l,k,a,b->l);
			b->pull();
		}
	}
	void push_back(T x){
		root = merge(root,new node(x));
	}
	void push_front(T x){
		root = merge(new node(x),root);
	}
	void erase(int l,int r){
		node *a,*b,*c;
		split(root,l,a,b);
		split(b,r-l+1,b,c);
		delete b;
		root = merge(a,c);
	}
	void insert(int idx,T k){
		node *a,*b;
		split(root,idx,a,b);
		root = merge(a,merge(new node(k),b));
	}
	T operator [](int x){
		node *a,*b,*c;
		split(root,x,a,b);
		split(b,1,b,c);
		root = merge(a,merge(b,c));
		return b->key;
	}
	void reverse(int l,int r){
		node *a,*b,*c;
		split(root,l,a,b);
		split(b,r-l+1,b,c);
		b->rev^=1;
		root = merge(a,merge(b,c));
	}
};
