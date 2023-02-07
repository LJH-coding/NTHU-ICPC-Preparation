// @return $x, y$ s.t. $ax + by = \gcd(a, b)$
ll ext_gcd(ll a, ll b, ll& x, ll& y) {
	if(b == 0) {
		x = 1; y = 0;
		return a;
	}
	ll x2, y2;
	ll c = a % b;
	if(c < 0) c += b;
	ll g = ext_gcd(b, c, x2, y2);
	x = y2;
	y = x2 - (a / b) * y2;
	return g;
}
