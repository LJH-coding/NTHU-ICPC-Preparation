template<class S,
		S (*node_pull)(S, S),
		S (*node_init)(S), 
		class T,
		S (*mapping)(S, T),
		T (*tag_pull)(T, T),
		T (*tag_init)()>
struct Treap{
	struct node{
		node *l = NULL,*r = NULL,*p = NULL;
		int pri = rand(),sz = 1;
		S info;
		T tag = tag_init();
		bool rev;
		node(S k) : info(k){}
		~node(){
			for(auto &i:{l,r})
				delete i;
		}
		void all_apply(T t,bool is_rev){
			if(is_rev){
				swap(l,r);
				rev^=1;
			}
			info = mapping(info, t);
			tag = tag_pull(tag, t);
		}
		void push(){
			for(auto &i:{l,r})
				if(i)i->all_apply(tag, rev);
			tag = tag_init();
			rev = 0;
		}
		void pull(){
			sz = 1,info = node_init(info);
			for(auto &i:{l,r}){
				if(i){
					sz+=i->sz,i->p = this;
					info = node_pull(info,i->info);
				}
			}
		}
	};
	node *root = NULL;
	int size(node *a){
		return a?a->sz:0;
	}
	int size(){
		return size(root);
	}
	node *merge(node *a,node *b){
		if(!a or !b)return a?:b;
		if(a->pri>b->pri){
			a->push();
			a->r = merge(a->r,b);
			a->r->p = a;
			a->pull();
			return a;
		}
		else{
			b->push();
			b->l = merge(a,b->l);
			b->l->p = b;
			b->pull();
			return b;
		}
	}
	void split(node *t, long long k, node *&a, node *&b, bool bst){
		if(!t){a = b = NULL;return;}
		t->push();
		if((bst==0 and size(t->l)+1<=k) or (bst==1 and t->info.key<=k)){
			a = t;
			split(t->r, ( bst ? k : k - size(t->l) - 1 ), a->r, b, bst);
			if(b)b->p = NULL;
			a->pull();
		}
		else{
			b = t;
			split(t->l, k, a, b->l, bst);
			if(a)a->p = NULL;
			b->pull();
		}
	}
	node *insert(long long idx, S x,bool bst = 0){
		node *a,*b;
		split(root, idx, a, b, bst);
		node *tmp = new node(x);
		root = merge(a, merge(tmp, b));
		return tmp;
	}
	void erase(long long l,long long r,bool bst = 0){
		node *a,*b,*c;
		split(root, (bst? l-1 : l), a, b, bst);
		split(b, (bst? r : r - l + 1), b, c, bst);
		delete b;
		root = merge(a,c);
	}
	S operator [](int x){
		node *a, *b, *c;
		split(root, x, a, b, 0);
		split(b, 1, b, c, 0);
		assert(b!=NULL);
		S ans = b->info;
		root = merge(a, merge(b, c));
		return ans;
	}
	void update(long long l,long long r,T t,bool bst = 0){
		node *a, *b, *c;
		split(root, (bst? l - 1 : l), a, b, bst);
		split(b, (bst? r : r - l + 1), b, c, bst);
		if(b)b->all_apply(t, 0);
		root = merge(a, merge(b, c));
	}
	void reverse(long long l,long long r,bool bst = 0){
		node *a, *b, *c;
		split(root, (bst? l - 1 : l), a, b, bst);
		split(b, (bst? r : r - l + 1), b, c, bst);
		if(b)b->all_apply(tag_init(), 1);
		root = merge(a, merge(b, c));
	}
	S query(long long l,long long r,bool bst = 0){
		node *a, *b, *c;
		split(root, (bst? l - 1 : l), a, b, bst);
		split(b, (bst? r : r - l + 1), b, c, bst);
		assert(b!=NULL);
		S ans = b->info;
		root = merge(a, merge(b, c));
		return  ans;
	}
};
