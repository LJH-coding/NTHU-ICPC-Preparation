template<int id>
struct modint {
public:
	static constexpr int mod() { return id; }

	constexpr modint() : value(0) {}
	modint(long long x) : value(x % mod()) {
		if(value < 0) value += mod();
	}

	constexpr int val() const { return value; }

	constexpr modint inv() const {
		return Pow(value, mod()-2, mod());
	}

	constexpr modint& operator+=(const modint& rhs) & {
		value += rhs.value;
		if(value >= mod()) {
			value -= mod();
		}
		return *this;
	}

	constexpr modint& operator-=(const modint& rhs) & {
		value -= rhs.value;
		if(value < 0) {
			value += mod();
		}
		return *this;
	}

	constexpr modint& operator*=(const modint& rhs) & {
		value = 1LL * value * rhs.value % mod();
		return *this;
	}

	constexpr modint& operator/=(const modint& rhs) & {
		return *this *= rhs.inv();
	}

	friend constexpr modint operator+(modint lhs, modint rhs) { return lhs += rhs; }
	friend constexpr modint operator-(modint lhs, modint rhs) { return lhs -= rhs; }
	friend constexpr modint operator*(modint lhs, modint rhs) { return lhs *= rhs; }
	friend constexpr modint operator/(modint lhs, modint rhs) { return lhs /= rhs; }
	constexpr modint operator+() const { return *this; }
	constexpr modint operator-() const { return modint() - *this; }
	constexpr bool operator==(const modint& rhs) const { return value == rhs.value; }
	constexpr bool operator!=(const modint& rhs) const { return value != rhs.value; }


	int value;
};
using mint = modint<mod>;
