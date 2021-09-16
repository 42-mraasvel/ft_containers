#include "testing.hpp"
#include <cassert>
#include <cstdlib>
#include <vector>

# include <set>
# include "containers/set.hpp"

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

template <typename Container>
void SetConstruct() {
	const int TOTAL = 1 * MILLION;
	Container m;

	for (int i = 0; i < TOTAL; ++i) {
		m.insert(i);
	}

	Container m2(m.begin(), m.end());

	Container m3(m);
}

template <typename Container>
void SetAssign() {
	const int TOTAL = 5 * MILLION;
	Container m;

	for (int i = 0; i < TOTAL; ++i) {
		m.insert(i);
	}

	Container m2;
	m2 = m;
}

template <typename Container>
void SetIterate() {
	const int TOTAL = 5 * MILLION;

	Container m;

	for (int i = 0; i < TOTAL; ++i) {
		m.insert(i);
	}

	for (typename Container::iterator it = m.begin(); it != m.end(); ++it) {
		;
	}

	for (typename Container::reverse_iterator rit = m.rbegin(); rit != m.rend(); ++rit) {
		;
	}
}

template <typename Container>
void SetInsert() {
	Container m;

	const int TOTAL = 5 * MILLION;

	for (int i = 0; i < TOTAL; ++i) {
		m.insert(i);
	}

	m.clear();

	for (int i = TOTAL; i >= 0; --i) {
		m.insert(i);
	}
}

template <typename Container>
void SetErase() {
	Container m;

	const int TOTAL = 5 * MILLION;

	for (int i = 0; i < TOTAL; ++i) {
		m.insert(i);
	}

	for (int i = 0; i < TOTAL; ++i) {
		m.erase(i);
	}
}

template <typename Container>
void SetSwap() {
	Container m1;
	Container m2;

	const int TOTAL1 = 5 * MILLION;
	const int TOTAL2 = TOTAL1 / 2;

	for (int i = 0; i < TOTAL1; ++i) {
		m1.insert(i);
		if (i < TOTAL2) {
			m2.insert(i);
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

template <typename Container>
void SetClear() {
	Container m1;

	const int TOTAL = 5 * MILLION;

	for (int i = 0; i < TOTAL; ++i) {
		m1.insert(i);
	}

	m1.clear();
	m1.clear();
	for (int i = 0; i < TOTAL; ++i) {
		m1.insert(i);
	}
	m1.clear();

}

template <typename Container>
void SetFind() {
	Container m1;

	const int TOTAL = 5 * MILLION;

	for (int i = 0; i < TOTAL; ++i) {
		m1.insert(i);
	}

	m1.find(5);
	m1.find(TOTAL / 2);
	m1.find(TOTAL);
	m1.find(TOTAL - 1);

}

template <typename Container>
void SetCount() {
	Container m1;

	const int TOTAL = 5 * MILLION;

	for (int i = 0; i < TOTAL; ++i) {
		m1.insert(i);
	}

	m1.count(5);
	m1.count(TOTAL / 2);
	m1.count(TOTAL);
	m1.count(TOTAL - 1);
}

template <typename Container>
void SetLowerbound() {
	Container m1;

	const int TOTAL = 5 * MILLION;

	for (int i = 0; i < TOTAL; ++i) {
		m1.insert(i);
	}

	m1.lower_bound(5);
	m1.lower_bound(TOTAL / 2);
	m1.lower_bound(TOTAL);
	m1.lower_bound(TOTAL - 1);
}

template <typename Container>
void SetUpperbound() {
	Container m1;

	const int TOTAL = 5 * MILLION;

	for (int i = 0; i < TOTAL; ++i) {
		m1.insert(i);
	}

	m1.upper_bound(5);
	m1.upper_bound(TOTAL / 2);
	m1.upper_bound(TOTAL);
	m1.upper_bound(TOTAL - 1);
}

template <typename Container>
void SetEqualrange() {
	Container m1;

	const int TOTAL = 5 * MILLION;

	for (int i = 0; i < TOTAL; ++i) {
		m1.insert(i);
	}

	m1.equal_range(5);
	m1.equal_range(TOTAL / 2);
	m1.equal_range(TOTAL);
	m1.equal_range(TOTAL - 1);
}

void SetTests() {

	double std_total = 0;
	double ft_total = 0;

	// Construct
	std_total += BenchmarkTest(SetConstruct<std::set<int> >, "SetConstruct", "std");
	ft_total += BenchmarkTest(SetConstruct<ft::set<int> >, "SetConstruct", "ft");

	// Construct
	std_total += BenchmarkTest(SetAssign<std::set<int> >, "SetAssign", "std");
	ft_total += BenchmarkTest(SetAssign<ft::set<int> >, "SetAssign", "ft");

	// Iterate
	std_total += BenchmarkTest(SetIterate<std::set<int> >, "SetIterate", "std");
	ft_total += BenchmarkTest(SetIterate<ft::set<int> >, "SetIterate", "ft");

	// Insert
	std_total += BenchmarkTest(SetInsert<std::set<int> >, "SetInsert", "std");
	ft_total += BenchmarkTest(SetInsert<ft::set<int> >, "SetInsert", "ft");

	// Erase
	std_total += BenchmarkTest(SetErase<std::set<int> >, "SetErase", "std");
	ft_total += BenchmarkTest(SetErase<ft::set<int> >, "SetErase", "ft");

	// Swap
	std_total += BenchmarkTest(SetSwap<std::set<int> >, "SetSwap", "std");
	ft_total += BenchmarkTest(SetSwap<ft::set<int> >, "SetSwap", "ft");

	// Clear
	std_total += BenchmarkTest(SetClear<std::set<int> >, "SetClear", "std");
	ft_total += BenchmarkTest(SetClear<ft::set<int> >, "SetClear", "ft");

	// Find
	std_total += BenchmarkTest(SetFind<std::set<int> >, "SetFind", "std");
	ft_total += BenchmarkTest(SetFind<ft::set<int> >, "SetFind", "ft");

	// Count
	std_total += BenchmarkTest(SetCount<std::set<int> >, "SetCount", "std");
	ft_total += BenchmarkTest(SetCount<ft::set<int> >, "SetCount", "ft");

	// SetLowerbound
	std_total += BenchmarkTest(SetLowerbound<std::set<int> >, "SetLowerbound", "std");
	ft_total += BenchmarkTest(SetLowerbound<ft::set<int> >, "SetLowerbound", "ft");

	// SetUpperbound
	std_total += BenchmarkTest(SetUpperbound<std::set<int> >, "SetUpperbound", "std");
	ft_total += BenchmarkTest(SetUpperbound<ft::set<int> >, "SetUpperbound", "ft");

	// SetEqualrange
	std_total += BenchmarkTest(SetEqualrange<std::set<int> >, "SetEqualrange", "std");
	ft_total += BenchmarkTest(SetEqualrange<ft::set<int> >, "SetEqualrange", "ft");

	std::cout << std::endl;
	std::cout << "STD_TOTAL = " << std_total << std::endl;
	std::cout << " FT_TOTAL = " << ft_total << std::endl;
}

}

