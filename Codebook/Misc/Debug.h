#ifdef LOCAL
	#define eprintf(...) { fprintf(stderr, __VA_ARGS__); fflush(stderr); }
#else
	#define eprintf(...) 42
#endif
