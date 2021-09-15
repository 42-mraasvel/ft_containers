#include "settings.hpp"
#include "testing.hpp"
#include <cassert>

# include <vector>
# include "containers/vector.hpp"

namespace Testing {

template <typename Container>
void VectorInsert() {
	Container v;

	const int TOTAL = 250 * MILLION;

	for (int i = 0; i < TOTAL; ++i) {
		v.push_back(i);
	}

	v.clear();
	v.reserve(TOTAL);
	for (int i = 0; i < TOTAL; ++i) {
		v.push_back(i);
	}
}



void VectorTests() {
	BenchmarkTest(VectorInsert<std::vector<int> >, "Vector Insert", "std");
	BenchmarkTest(VectorInsert<ft::vector<int> >, "Vector Insert", "ft");
}

}

