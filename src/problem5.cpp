#include <array>
#include <cstdio>

enum Symbol {
	Nothing,
	Plus,
	Minus
};

using Symbols = std::array<Symbol,8>;

int evaluate( Symbols sym ) {
	std::array<int,9> values = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	// combine nothings
	for(int i=0;i<8;) {
		if( sym[i] == Nothing ) {
			values[i] = values[i] * 10 + values[i+1];
			
			// shift all the rest down
			for(int j=i+1;j<8;++j)
				values[j] = values[j+1];
			values[8] = 0;
			
			for(int j=i;j<7;++j)
				sym[j] = sym[j+1];
			sym[7] = Plus;
		} else {
			++i;
		}
	}
	int sum = values[0];
	for(int i=0;i<8;++i) {
		if( sym[i] == Minus )
			sum -= values[i+1];
		else
			sum += values[i+1];
	}
	return sum;
}

bool next_combination( Symbols& sym ) {
	for(int i=0;i<8;++i) {
		if( sym[i] != Minus ) {
			sym[i] = Symbol((int)sym[i] + 1);
			break;
		} else {
			sym[i] = Nothing;
			if( i == 7 )
				return false;
		}
	}
	return true;
}

void print( const Symbols& sym ) {
	for(int i=0;i<8;++i) {
		printf("%d",i+1);
		switch( sym[i] ) {
		case Plus:
			printf(" + ");
			break;
		case Minus:
			printf(" - ");
			break;
		}
	}
	printf("9\n");
}

int main() {
	Symbols sym = {};
	do {
		if( evaluate( sym ) == 100 )
			print( sym );
	} while( next_combination( sym ) );
}