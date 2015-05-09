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

// concatenates the digits of the numbers in seq in the given base
template<typename Seq>
uint64_t concat_digits( const Seq& seq, uint64_t base ) {
	uint64_t result = 0;
	uint64_t m = 1;
	for( auto x : seq ) {
		result += x * m;
		m *= mag(x,base);
	}
	return result;
}

// brute force searches all permutations for the largest concat
template<typename Seq>
uint64_t largest_perm( Seq seq, uint64_t base ) {
	uint64_t largest = 0;
	do {
		auto x = concat_digits( seq, base );
		if( x > largest )
			largest = x;
	} while( std::next_permutation( seq.begin(), seq.end() ) );
	return largest;
}

int main() {
	std::array<int,4> values = { 505, 52, 1, 5059 };
	
	std::sort( values.begin(), values.end() );
	
	auto largest = largest_perm( values, 10 );

	printf("%llu\n",largest);
}
