template<class T>
struct Point{
	T x,y;
	Point(T x = 0,T y = 0) : x(x), y(y) {}
	Point operator + (const Point &b) const {
		return Point(x + b.x,y + b.y);
	}
	Point operator - (const Point &b) const {
		return Point(x - b.x,y - b.y);
	}
	Point operator * (T b) const {
		return Point(x*b,y*b);
	}
	Point operator / (T b) const {
		return Point(x/b,y/b);
	}
	T operator * (const Point &b) const {
		return x * b.x + y * b.y;
	}
	T operator ^ (const Point &b) const {
		return x * b.y - y * b.x;
	}
	bool operator < (const Point &b) const {
		return atan2l(y,x)<atan2l(b.y,b.x);
	}
};
