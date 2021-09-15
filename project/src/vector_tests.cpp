#include "settings.hpp"
#include "testing.hpp"
#include <cassert>

# include <vector>
# include "containers/vector.hpp"

namespace Testing {

template <typename Container>
void VectorInsert() {
	Container v;

	// v.reserve(100 * MILLION);
	for (int i = 0; i < 250 * MILLION; ++i) {
		v.push_back(i);
	}

	assert(v.size() == 250 * MILLION);
}

void VectorTests() {
	BenchmarkTest(VectorInsert<std::vector<int> >, "Vector Insert", "std");
	BenchmarkTest(VectorInsert<ft::vector<int> >, "Vector Insert", "ft");
}

}

