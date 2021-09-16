#include "testing.hpp"
#include <cassert>
#include <cstdlib>
#include <vector>

# include <map>
# include "containers/map.hpp"

/*
TESTS:
	Constructors
	Operator=
	Iterating
	Accessing Element / assigning
	Insert
	Erase
	Swap
	Clear
	Find
	Count
	Lower_bound
	Upper_bound
	Equal_range

*/

namespace Testing {

template <typename Container, typename Pairtype>
void MapConstruct() {
	const int TOTAL = 1 * MILLION;
	Container m;

	for (int i = 0; i < TOTAL; ++i) {
		m[i] = i;
	}

	Container m2(m.begin(), m.end());

	Container m3(m);
}

template <typename Container, typename PairType>
void MapAssign() {
	const int TOTAL = 5 * MILLION;
	Container m;

	for (int i = 0; i < TOTAL; ++i) {
		m[i] = i;
	}

	Container m2;
	m2 = m;
}

template <typename Container, typename PairType>
void MapIterate() {
	const int TOTAL = 5 * MILLION;

	Container m;

	for (int i = 0; i < TOTAL; ++i) {
		m[i] = i;
	}

	for (typename Container::iterator it = m.begin(); it != m.end(); ++it) {
		it->second = 42;
	}

	for (typename Container::reverse_iterator rit = m.rbegin(); rit != m.rend(); ++rit) {
		rit->second = 69;
	}
}

template <typename Container, typename PairType>
void MapInsert() {
	Container m;

	const int TOTAL = 5 * MILLION;

	for (int i = 0; i < TOTAL; ++i) {
		m.insert(PairType(i, i));
	}

	m.clear();

	for (int i = TOTAL; i >= 0; --i) {
		m[i] = i;
	}
}

template <typename Container, typename PairType>
void MapErase() {
	Container m;

	const int TOTAL = 5 * MILLION;

	for (int i = 0; i < TOTAL; ++i) {
		m[i] = i;
	}

	for (int i = 0; i < TOTAL; ++i) {
		m.erase(i);
	}
}

template <typename Container, typename PairType>
void MapSwap() {
	Container m1;
	Container m2;

	const int TOTAL1 = 5 * MILLION;
	const int TOTAL2 = TOTAL1 / 2;

	for (int i = 0; i < TOTAL1; ++i) {
		m1[i] = i;
		if (i < TOTAL2) {
			m2[i] = i;
		}
	}

	assert(m1.size() == TOTAL1);
	assert(m2.size() == TOTAL2);

	typename Container::iterator it = m1.begin();

	m1.swap(m2);
	assert(it == m2.begin());
	assert(m1.size() == TOTAL2);
	assert(m2.size() == TOTAL1);
	m2.swap(m1);
	assert(it == m1.begin());

}

template <typename Container, typename PairType>
void MapClear() {
	Container m1;

	const int TOTAL = 5 * MILLION;

	for (int i = 0; i < TOTAL; ++i) {
		m1[i] = i;
	}

	m1.clear();
	m1.clear();
	for (int i = 0; i < TOTAL; ++i) {
		m1[i] = i;
	}
	m1.clear();

}

template <typename Container, typename PairType>
void MapFind() {
	Container m1;

	const int TOTAL = 5 * MILLION;

	for (int i = 0; i < TOTAL; ++i) {
		m1[i] = i;
	}

	m1.find(5);
	m1.find(TOTAL / 2);
	m1.find(TOTAL);
	m1.find(TOTAL - 1);

}

template <typename Container, typename PairType>
void MapCount() {
	Container m1;

	const int TOTAL = 5 * MILLION;

	for (int i = 0; i < TOTAL; ++i) {
		m1[i] = i;
	}

	m1.count(5);
	m1.count(TOTAL / 2);
	m1.count(TOTAL);
	m1.count(TOTAL - 1);
}

template <typename Container, typename PairType>
void MapLowerbound() {
	Container m1;

	const int TOTAL = 5 * MILLION;

	for (int i = 0; i < TOTAL; ++i) {
		m1[i] = i;
	}

	m1.lower_bound(5);
	m1.lower_bound(TOTAL / 2);
	m1.lower_bound(TOTAL);
	m1.lower_bound(TOTAL - 1);
}

template <typename Container, typename PairType>
void MapUpperbound() {
	Container m1;

	const int TOTAL = 5 * MILLION;

	for (int i = 0; i < TOTAL; ++i) {
		m1[i] = i;
	}

	m1.upper_bound(5);
	m1.upper_bound(TOTAL / 2);
	m1.upper_bound(TOTAL);
	m1.upper_bound(TOTAL - 1);
}

template <typename Container, typename PairType>
void MapEqualrange() {
	Container m1;

	const int TOTAL = 5 * MILLION;

	for (int i = 0; i < TOTAL; ++i) {
		m1[i] = i;
	}

	m1.equal_range(5);
	m1.equal_range(TOTAL / 2);
	m1.equal_range(TOTAL);
	m1.equal_range(TOTAL - 1);
}

void MapTests() {

	double ft_total = 0;
	double std_total = 0;

	// Construct
	std_total += BenchmarkTest(MapConstruct<std::map<int, int>, std::pair<int, int> >, "MapConstruct", "std");
	ft_total += BenchmarkTest(MapConstruct<ft::map<int, int>, ft::pair<int, int> >, "MapConstruct", "ft");

	// Construct
	std_total += BenchmarkTest(MapAssign<std::map<int, int>, std::pair<int, int> >, "MapAssign", "std");
	ft_total += BenchmarkTest(MapAssign<ft::map<int, int>, ft::pair<int, int> >, "MapAssign", "ft");

	// Iterate
	std_total += BenchmarkTest(MapIterate<std::map<int, int>, std::pair<int, int> >, "MapIterate", "std");
	ft_total += BenchmarkTest(MapIterate<ft::map<int, int>, ft::pair<int, int> >, "MapIterate", "ft");

	// Insert
	std_total += BenchmarkTest(MapInsert<std::map<int, int>, std::pair<int, int> >, "MapInsert", "std");
	ft_total += BenchmarkTest(MapInsert<ft::map<int, int>, ft::pair<int, int> >, "MapInsert", "ft");

	// Erase
	std_total += BenchmarkTest(MapErase<std::map<int, int>, std::pair<int, int> >, "MapErase", "std");
	ft_total += BenchmarkTest(MapErase<ft::map<int, int>, ft::pair<int, int> >, "MapErase", "ft");

	// Swap
	std_total += BenchmarkTest(MapSwap<std::map<int, int>, std::pair<int, int> >, "MapSwap", "std");
	ft_total += BenchmarkTest(MapSwap<ft::map<int, int>, ft::pair<int, int> >, "MapSwap", "ft");

	// Clear
	std_total += BenchmarkTest(MapClear<std::map<int, int>, std::pair<int, int> >, "MapClear", "std");
	ft_total += BenchmarkTest(MapClear<ft::map<int, int>, ft::pair<int, int> >, "MapClear", "ft");

	// Find
	std_total += BenchmarkTest(MapFind<std::map<int, int>, std::pair<int, int> >, "MapFind", "std");
	ft_total += BenchmarkTest(MapFind<ft::map<int, int>, ft::pair<int, int> >, "MapFind", "ft");

	// Count
	std_total += BenchmarkTest(MapCount<std::map<int, int>, std::pair<int, int> >, "MapCount", "std");
	ft_total += BenchmarkTest(MapCount<ft::map<int, int>, ft::pair<int, int> >, "MapCount", "ft");

	// MapLowerbound
	std_total += BenchmarkTest(MapLowerbound<std::map<int, int>, std::pair<int, int> >, "MapLowerbound", "std");
	ft_total += BenchmarkTest(MapLowerbound<ft::map<int, int>, ft::pair<int, int> >, "MapLowerbound", "ft");

	// MapUpperbound
	std_total += BenchmarkTest(MapUpperbound<std::map<int, int>, std::pair<int, int> >, "MapUpperbound", "std");
	ft_total += BenchmarkTest(MapUpperbound<ft::map<int, int>, ft::pair<int, int> >, "MapUpperbound", "ft");

	// MapEqualrange
	std_total += BenchmarkTest(MapEqualrange<std::map<int, int>, std::pair<int, int> >, "MapEqualrange", "std");
	ft_total += BenchmarkTest(MapEqualrange<ft::map<int, int>, ft::pair<int, int> >, "MapEqualrange", "ft");
	std::cout << std::endl;
	std::cout << "STD_TOTAL = " << std_total << std::endl;
	std::cout << " FT_TOTAL = " << ft_total << std::endl;
}

}

