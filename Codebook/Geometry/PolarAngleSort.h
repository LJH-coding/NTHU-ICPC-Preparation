template<class T>
bool cmp(const Point<T> &a,const Point<T> &b){
	int lhs = (a.y < 0 || a.y==0 && a.x > 0) ? 0 : (1 + (a.x != 0 || a.y != 0));
	int rhs = (b.y < 0 || b.y==0 && b.x > 0) ? 0 : (1 + (b.x != 0 || b.y != 0));
	if(lhs != rhs) {
		return lhs < rhs;
	}
	long long area = (a^b);
	return area ? area > 0 : abs(a.x) + abs(a.y) < abs(b.x) + abs(b.y);
}
