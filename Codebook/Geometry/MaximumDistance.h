template<class T>
T MaximumDistance(vector<Point<T>>&p){
	vector<Point<T>>C = ConvexHull(p);
	int n = C.size(),t = 2;
	T ans = 0;
	for(int i = 0;i<n;i++){
		while(((C[i]-C[t])^(C[(i+1)%n]-C[t]))<((C[i]-C[(t+1)%n])^(C[(i+1)%n]-C[(t+1)%n])))t = (t+1)%n;
		ans = max({ans,abs2(C[i]-C[t]),abs2(C[(i+1)%n]-C[t])});
	}
	return ans;
}
