template<class T>
vector<Point<T>> ConvexHull(vector<Point<T>>&p){
    sort(all(p),[&](Point<T>a,Point<T>b){
		if(a.x!=b.x)return a.x<b.x;
		return a.y<b.y;
	});
	vector<Point<T>>hull;
    hull.clear();
    for(auto i : p){
        while(hull.size() > 1 && 
			((i-hull[hull.size()-2])^(hull.back()-hull[hull.size()-2]))>=0)
            hull.pop_back();
        hull.push_back(i);
    }
    int sz = hull.size();
    hull.pop_back();
    reverse(all(p));
    for(auto i : p){
        while(hull.size() > sz && 
			((i-hull[hull.size()-2])^(hull.back()-hull[hull.size()-2]))>=0)
            hull.pop_back();
        hull.push_back(i);
    }
    hull.pop_back();
	return hull;
}
