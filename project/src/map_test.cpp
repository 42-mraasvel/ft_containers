#include "settings.hpp"
#include "testing.hpp"
#include <cassert>
#include <cstdlib>
#include <vector>

# include <map>
# include "containers/map.hpp"

namespace Testing {

template <typename Container, typename PairType>
void MapInsert() {
	Container m;

	const int TOTAL = 1 * MILLION;

	for (int i = 0; i < TOTAL; ++i) {
		m.insert(PairType(i, i));
	}

	m.clear();

	for (int i = TOTAL; i >= 0; --i) {
		m.insert(PairType(i, i));
	}
}

void MapTests() {
	BenchmarkTest(MapInsert<std::map<int, int>, std::pair<int, int> >, "Map Insert", "std");
	BenchmarkTest(MapInsert<ft::map<int, int>, ft::pair<int, int> >, "Map Insert", "ft");
}

}

