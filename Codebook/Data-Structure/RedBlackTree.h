template<class T, typename cmp=less<>>struct _tree{//#include<bits/extc++.h>
	tree<pair<T,int>,null_type,cmp,rb_tree_tag,tree_order_statistics_node_update>st;
	int id = 0;
	void insert(T x){st.insert({x,id++});}
	void erase(T x){st.erase(st.lower_bound({x,0}));}
	int order_of_key(T x){return st.order_of_key(*st.lower_bound({x,0}));}
	T find_by_order(T x){return st.find_by_order(x)->first;}
	T lower_bound(T x){return st.lower_bound({x,0})->first;}
	T upper_bound(T x){return st.upper_bound({x,(int)1e9+7})->first;}
	T smaller_bound(T x){return (--st.lower_bound({x,0}))->first;}
};
