// return the maximum of $f(x)$ in $[l, r]$
double ternary_search(double l, double r) {
	while(r - l > EPS) {
		double m1 = l + (r - l) / 3;
		double m2 = r - (r - l) / 3;
		double f1 = f(m1), f2 = f(m2);
		if(f1 < f2) l = m1;
		else r = m2;
	}
	return f(l);
}

// return the maximum of $f(x)$ in $(l, r]$
int ternary_search(int l, int r) {
	while(r - l > 1) {
		int mid = (l + r) / 2;
		if(f(m) > f(m + 1)) r = m;
		else l = m;
	}
	return r;
}
