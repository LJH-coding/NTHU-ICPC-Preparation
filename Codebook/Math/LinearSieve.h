vector<bool> is_prime;
vector<int> primes, phi, mobius, least;
void linear_sieve(int n) {
	n += 1;
	is_prime.resize(n);
	least.resize(n);
	fill(2 + begin(is_prime),end(is_prime), true);
	phi.resize(n); mobius.resize(n);
	phi[1] = mobius[1] = 1;
	least[0] = 0,least[1] = 1;
	for(int i = 2; i < n; ++i) {
		if(is_prime[i]) {
			primes.push_back(i);
			phi[i] = i - 1;
			mobius[i] = -1;
			least[i] = i;
		}
		for(auto j : primes) {
			if(i * j >= n) break;
			is_prime[i * j] = false;
			least[i * j] = j;
			if(i % j == 0) {
				mobius[i * j] = 0;
				phi[i * j] = phi[i] * j;
				break;
			} else {
				mobius[i * j] = mobius[i] * mobius[j];
				phi[i * j] = phi[i] * phi[j];
			}
		}
	}
}
