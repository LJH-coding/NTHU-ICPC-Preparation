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
};
int sign(double a){
	return fabs(a) < eps ? 0 : a > 0 ? 1 : -1;
}
template<class T>
double abs(const Point<T>&p){
	return sqrtl(p*p);
}
template<class T>
T abs2(const Point<T>&p){
	return p*p;
}
template<class T>
int ori(Point<T> a,Point<T> b,Point<T> c){
	return sign((b-a)^(c-a));
}
template<class T>
bool collinearity(Point<T> p1,Point<T> p2,Point<T> p3){
	return sign((p1-p3)^(p2-p3)) == 0;
}
template<class T>
bool btw(Point<T> p1,Point<T> p2,Point<T> p3) {
	if(!collinearity(p1, p2, p3)) return 0;
	return sign((p1-p3)*(p2-p3)) <= 0;
}
template<class T>
bool PointOnSegment(const Point<T> &p1,const Point<T> &p2, const Point<T> &p3){
	return collinearity(p1,p2,p3) && btw(p1,p2,p3);
}
template<class T>
bool seg_intersect(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4) {
	int a123 = ori(p1, p2, p3);
	int a124 = ori(p1, p2, p4);
	int a341 = ori(p3, p4, p1);
	int a342 = ori(p3, p4, p2);
	if(a123 == 0 && a124 == 0)
		return btw(p1, p2, p3) || btw(p1, p2, p4) || btw(p3, p4, p1) || btw(p3, p4, p2);
	return a123 * a124 <= 0 && a341 * a342 <= 0;
}
template<class T>
double area(vector<Point<T>> v){
	if(v.size()<=2)return 0;
	double ans = 0;
	for(int i = 1;i<v.size()-1;++i){
		ans+=((v[i]-v[0])^(v[i+1]-v[0]));	
	}
	return abs(ans)/2.;
}
