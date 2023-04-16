template<class T>
int PointInPolygon(const vector<Point<T>> &Poly, const Point<T> p){
	int ans = 0;
	for(auto a = --Poly.end(),b = Poly.begin();b!=Poly.end();a = b++){
		if(PointOnSegment(*a,*b,p)){
			return -1;
		}
		if(seg_intersect(p,p+Point<T>(2e9+7,1),*a,*b)){
			ans = !ans;
		}
	}	
	return ans;
}
