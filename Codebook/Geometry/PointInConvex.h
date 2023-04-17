template<class T>
int PointInConvex(const vector<Point<T>>&C,const Point<T>&p){
	if(btw(C[0],C[1],p) || btw(C[0],C.back(),p))return -1;
	int l = 0,r = (int)C.size()-1;
	while(l<=r){
		int m = (l+r)>>1;
		auto a1 = (C[m]-C[0])^(p-C[0]);
		auto a2 = (C[(m+1)%C.size()]-C[0])^(p-C[0]);
		if(a1>=0 and a2<=0){
			auto res = (C[(m+1)%C.size()]-C[m])^(p-C[m]);
			return res > 0 ? 1 : (res >= 0 ? -1 : 0);
		}
		if(a1 < 0) r = m-1;
		else l = m+1;
	}
	return 0;
}
