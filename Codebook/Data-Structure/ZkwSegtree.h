template<class S,
         S (*node_pull)(S, S),
         S (*node_init)(),
         class F,
         S (*mapping)(S, F),
         F (*tag_pull)(F, F),
         F (*tag_init)()>
class segment_tree {
public:
	segment_tree() : segment_tree(0) {}
	explicit segment_tree(int _n) : segment_tree(vector<S>(_n, node_init())) {}
	explicit segment_tree(const vector<S>& v) : n((int) v.size()) {
		log = std::__lg(2 * n - 1);
		size = 1 << log;
		d = vector<S>(size << 1, node_init());
		lz = vector<F>(size, tag_init());
		for(int i = 0; i < n; i++) {
			d[size + i] = v[i];
		}
		for(int i = size - 1; i; --i) {
			update(i);
		}
	}
	void set(int p, S x) {
		assert(0 <= p && p < n);
		p += size;
		for(int i = log; i; --i) {
			push(p >> i);
		}
		d[p] = x;
		for(int i = 1; i <= log; ++i) {
			update(p >> i);
		}
	}
	S get(int p) {
		assert(0 <= p && p < n);
		p += size;
		for(int i = log; i; i--) {
			push(p >> i);
		}
		return d[p];
	}
	S operator[](int p) {
		return get(p);
	}
	S query(int l, int r) {
		r++;
		assert(l<=r);
		l += size;
		r += size;
		for(int i = log; i; i--) {
			if(((l >> i) << i) != l) {
				push(l >> i);
			}
			if(((r >> i) << i) != r) {
				push(r >> i);
			}
		}
		S sml = node_init(), smr = node_init();
		while(l < r) {
			if(l & 1) {
				sml = node_pull(sml, d[l++]);
			}
			if(r & 1) {
				smr = node_pull(d[--r], smr);
			}
			l >>= 1;
			r >>= 1;
		}
		return node_pull(sml, smr);
	}
	void apply(int p, F f) {
		assert(0 <= p && p < n);
		p += size;
		for(int i = log; i; i--) {
			push(p >> i);
		}
		d[p] = mapping(f, d[p]);
		for(int i = 1; i <= log; i++) {
			update(p >> i);
		}
	}
	void update(int l, int r, F f) {
		r++;
		assert(l<=r);
		l += size;
		r += size;
		for(int i = log; i; i--) {
			if(((l >> i) << i) != l) {
				push(l >> i);
			}
			if(((r >> i) << i) != r) {
				push((r - 1) >> i);
			}
		}
		{
			int l2 = l, r2 = r;
			while(l < r) {
				if(l & 1) {
					all_apply(l++, f);
				}
				if(r & 1) {
					all_apply(--r, f);
				}
				l >>= 1;
				r >>= 1;
			}
			l = l2;
			r = r2;
		}
		for(int i = 1; i <= log; i++) {
			if(((l >> i) << i) != l) {
				update(l >> i);
			}
			if(((r >> i) << i) != r) {
				update((r - 1) >> i);
			}
		}
	}
private:
	int n, size, log;
	vector<S> d;
	vector<F> lz;
	inline void update(int k) { d[k] = node_pull(d[k << 1], d[k << 1 | 1]); }
	void all_apply(int k, F f) {
		d[k] = mapping(d[k], f);
		if(k < size) {
			lz[k] = tag_pull(lz[k], f);
		}
	}
	void push(int k) {
		all_apply(k << 1, lz[k]);
		all_apply(k << 1 | 1, lz[k]);
		lz[k] = tag_init();
	}
};
