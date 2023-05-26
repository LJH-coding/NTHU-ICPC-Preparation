//give you $a, b, m$ find $x$ such that $a^x \equiv m (\mod m)$
#line 2 "library/math/discrete-log.hpp"
#include <vector>
#include <cmath>
#include <cassert>
#line 2 "library/data-structure/pbds.hpp"
#include <ext/pb_ds/assoc_container.hpp>
#line 2 "library/random/splitmix64.hpp"
#include <chrono>

namespace felix {

namespace internal {

struct splitmix64_hash {
	// http://xoshiro.di.unimi.it/splitmix64.c

	static unsigned long long splitmix64(unsigned long long x) {
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}
 
	unsigned long long operator()(unsigned long long x) const {
		static const unsigned long long FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x + FIXED_RANDOM);
	}
};

} // namespace internal


} // namespace felix

#line 4 "library/data-structure/pbds.hpp"

namespace felix {

template<class T, class U, class H = internal::splitmix64_hash> using hash_map = __gnu_pbds::gp_hash_table<T, U, H>;
template<class T, class H = internal::splitmix64_hash> using hash_set = hash_map<T, __gnu_pbds::null_type, H>;

template<class T, class Comp = std::less<T>> using ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, Comp, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
template<class T> using ordered_multiset = ordered_set<T, std::less_equal<T>>;

} // namespace felix
#line 2 "library/modint/barrett.hpp"

namespace felix {

namespace internal {

// Fast modular multiplication by barrett reduction

// Reference: https://en.wikipedia.org/wiki/Barrett_reduction

struct barrett {
	unsigned int m;
	unsigned long long im;

	explicit barrett(unsigned int _m) : m(_m), im((unsigned long long)(-1) / _m + 1) {}

	unsigned int umod() const { return m; }

	unsigned int mul(unsigned int a, unsigned int b) const {
		unsigned long long z = a;
		z *= b;
#ifdef _MSC_VER
		unsigned long long x;
		_umul128(z, im, &x);
#else
		unsigned long long x = (unsigned long long)(((unsigned __int128)(z) * im) >> 64);
#endif
		unsigned long long y = x * m;
		return (unsigned int)(z - y + (z < y ? m : 0));
	}
};

} // namespace internal


} // namespace felix

#line 2 "library/math/binary-gcd.hpp"

namespace felix {

template<class T>
inline T binary_gcd(T a, T b) {
	if(a == 0 || b == 0) {
		return a | b;
	}
	int8_t n = __builtin_ctzll(a);
	int8_t m = __builtin_ctzll(b);
	a >>= n;
	b >>= m;
	while(a != b) {
		T d = a - b;
		int8_t s = __builtin_ctzll(d);
		bool f = a > b;
		b = f ? b : a;
		a = (f ? d : -d) >> s;
	}
	return a << (n < m ? n : m);
}

} // namespace felix

#line 8 "library/math/discrete-log.hpp"

namespace felix {

int discrete_log(int a, int b, int m) {
	assert(b < m);
	if(b == 1 || m == 1) {
		return 0;
	}
	int n = (int) std::sqrt(m) + 1, e = 1, f = 1, j = 1;
	hash_map<int, int> baby;
	internal::barrett bt(m);
	while(j <= n && (e = f = bt.mul(e, a)) != b) {
		baby[bt.mul(e, b)] = j++;
	}
	if(e == b) {
		return j;
	}
	if(binary_gcd(m, e) == binary_gcd(m, b))  {
		for(int i = 2; i < n + 2; i++) {
			e = bt.mul(e, f);
			if(baby.find(e) != baby.end()) {
				return n * i - baby[e];
			}
		}
	}
	return -1;
}

} // namespace felix
