#include <array>
#include <cstdio>
#include <cstdint>
#include <algorithm>

// returns the smallest power of base greater than x
uint64_t mag( uint64_t x, uint64_t base ) {
	uint64_t m = 1;
	while( x > 0 ) {
		x /= base;
		m *= base;
	}
	return m;
}

// concatenates the digits of the numbers in the given base
template<typename It>
uint64_t concat_digits( It p1, It p2, uint64_t base = 10 ) {
	uint64_t result = 0;
	uint64_t m = 1;
	for(;p1!=p2;++p1) {
		auto x = *p1;
		result += x * m;
		m *= mag(x,base);
	}
	return result;
}

int main() {
	std::array<int,4> values = { 505, 52, 1, 5059 };
	//std::array<int,13> values = {1,2,3,4,5,6,7,8,9,10,11,12,13};

	auto comp = []( int x, int y ) {
		int a[] = { x, y };
		int b[] = { y, x };
		auto c1 = concat_digits( a, a+2 );
		auto c2 = concat_digits( b, b+2 );
		return c1 > c2;
	};

	std::sort( values.begin(), values.end(), comp );

	auto largest = concat_digits( values.begin(), values.end() );

	printf("%llu\n",largest);
}
