template<class S,
		S (*node_pull)(S, S),
		S (*node_init)(),
		class T,
		S (*mapping)(S, pair<T, bool>),
		T (*tag_pull)(T, T),
		T (*tag_init)()>
struct Treap {
    struct node {
        node *l = NULL, *r = NULL, *p = NULL;
        const int pri = rand();
        int sz = 1;
        S key, ans;
        pair<T, bool> tag = {tag_init(), false};
        node(S k) : key(k), ans(k) {}
        void all_apply(pair<T, bool> t) {
            key = mapping(key, t);
            ans = mapping(ans, t);
            tag.second ^= t.second;
            tag.first = tag_pull(tag.first, t.first);
        }
        void push() {
            for(auto &i : {l,r})
                if(i) i->all_apply(tag);
            tag = {tag_init(), false};
        }
        void pull() {
            sz = 1, ans = key;
            if(l) sz += l->sz, l->p = this, ans = node_pull(l->ans, ans);
            if(r) sz += r->sz, r->p = this, ans = node_pull(ans, r->ans);
        }
    };
    int size(node *t) {
        return t ? t->sz : 0;
    }
    node *merge(node *a, node *b) {
        if(!a or !b) return a ? : b;
        if(a->pri>b->pri) {
            a->push();
            a->r = merge(a->r, b);
            a->r->p = a;
            a->pull();
            return a;
        }
        else {
            b->push();
            b->l = merge(a, b->l);
            b->l->p = b;
            b->pull();
            return b;
        }
    }
    void split_by_size(node *t, int k, node *&a, node *&b) {
        if(!t) {a = b = NULL; return;}
        t->push();
        if(size(t->l)+1<=k) {
            a = t;
            split_by_size(t->r, k - size(t->l) - 1 , a->r, b);
            if(b) b->p = NULL;
            a->pull();
        }
        else {
            b = t;
            split_by_size(t->l, k, a, b->l);
            if(a) a->p = NULL;
            b->pull();
        }
    }
    int find_next(node *t, S k) {
        if(!t)return 0;
        t->push();
        if(t->key < k) return size(t->l) + 1 + find_next(t->r, k);
        return find_next(t->l, k);
    }
    int find_prev(node *t, S k) {
        int pos = find_next(t, k);
        return pos - (pos >= this->size() || (*this)[pos] > k);
    }
    node *root;
    Treap(S s) : root(new node(s)) {}
    Treap(node *t = NULL) : root(t) {}
    tuple<Treap, Treap, Treap> split(int l, int r) {
        node *a, *b, *c;
        split_by_size(root, l, a, b);
        split_by_size(b, r - l + 1, b, c);
        root = NULL;
        return {a, b, c};
    }
    void merge(Treap &a) {
        root = merge(root, a.root);
        a.root = NULL;
    }
    void update(T t, bool rev) {
        root->all_apply({t, rev});
    }
    pair<S, S> query() {
        if(!root)return {node_init(), node_init()};
        root->push();
        return {root->key, root->ans};
    }
    S operator[](int pos) {
        auto [x, y, z] = split(pos, pos);
        S res = y.query().first;
        root = merge(x.root, merge(y.root, z.root));
        return res;
    }
    int size() {
        return size(root);
    }
    void clear(){
        auto dfs = [&](auto dfs, node *now) -> void {
            if(now->l)dfs(dfs, now->l);
            if(now->r)dfs(dfs, now->r);
            delete(now);
        };
        dfs(dfs, root);
    }
};
