#include "testing.hpp"
#include <cassert>

# include <vector>
# include <iostream>
# include "containers/vector.hpp"

/*

Important Benchmarks:
	Constructing
	Operator=
	push_back
	pop_back
	Iterating
	Clearing
	Swapping
	Resizing

	Insert
	Erase


*/

namespace Testing {

template <typename Container>
void VectorConstructor() {

	const int TOTAL = 250 * MILLION;

	Container v(TOTAL, 42);

	Container v2(v.begin(), v.end());

	Container v3(v2);

	assert(v.size() == TOTAL);
	assert(v2.size() == TOTAL);
	assert(v3.size() == TOTAL);

}

template <typename Container>
void VectorAssignment() {
	const int TOTAL1 = 250 * MILLION;
	Container v;

	for (int i = 0; i < TOTAL1; ++i) {
		v.push_back(i);
	}

	Container v2;

	v2 = v;

	Container v3;

	v3.assign(v.begin(), v.end());
}

template <typename Container>
void VectorPushback() {
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

template <typename Container>
void VectorPopback() {
	const int TOTAL = 500 * MILLION;

	Container v(TOTAL, 42);

	for (int i = 0; i < TOTAL; ++i) {
		v.pop_back();
	}

	assert(v.size() == 0);
}

template <typename Container>
void VectorIterating() {
	const int TOTAL = 500 * MILLION;
	Container v;

	v.reserve(TOTAL);
	for (int i = 0; i < TOTAL; ++i) {
		v.push_back(i);
	}

	typename Container::iterator it = v.begin();
	int i = 0;
	while (it != v.end()) {
		++i;
		++it;
	}

	assert(i == TOTAL);

	typename Container::reverse_iterator rit = v.rbegin();
	while (rit != v.rend()) {
		--i;
		++rit;
	}

	assert(i == 0);
}

template <typename Container>
void VectorClear() {
	const int TOTAL = 250 * MILLION;

	Container v;

	for (int i = 0; i < TOTAL; ++i) {
		v.push_back(i);
	}

	v.clear();
	v.clear();
	for (int i = 0; i < TOTAL; ++i) {
		v.push_back(i);
	}
	v.clear();
	for (int i = 0; i < TOTAL; ++i) {
		v.push_back(i);
	}
	v.clear();
}

template <typename Container>
void VectorSwap() {
	const int TOTAL = 100 * MILLION;

	Container v1;
	Container v2;
	for (int i = 0; i < TOTAL; ++i) {
		v1.push_back(i);
		if (i < TOTAL / 2) {
			v2.push_back(i);
		}
	}

	const typename Container::size_type s1 = v1.size();
	const typename Container::size_type s2 = v2.size();


	v1.swap(v2);
	assert(s1 == v2.size());
	assert(s2 == v1.size());
	v2.swap(v1);
	assert(s1 == v1.size());
	assert(s2 == v2.size());
}

template <typename Container>
void VectorResize() {
	const int ITERATIONS = 2;
	const int TOTAL = 500 * MILLION;
	for (int i = 0; i < ITERATIONS; ++i) {
		Container v;
		v.resize(TOTAL);
	}
}

template <typename Container>
void VectorInsert() {
	const int TOTAL = 500 * MILLION;
	const int POSITION = TOTAL / 10;

	Container v(TOTAL, 42);

	typename Container::iterator it = v.begin();
	for (int i = 0; i < POSITION; ++i) {
		++it;
	}

	v.insert(it, 69);
}

template <typename Container>
void VectorErase() {
	const int TOTAL = 500 * MILLION;
	const int POSITION = TOTAL / 10;

	Container v(TOTAL, 42);

	typename Container::iterator it = v.begin();
	for (int i = 0; i < POSITION; ++i) {
		++it;
	}

	v.erase(it);
}


void VectorTests() {

	double std_total = 0;
	double ft_total = 0;

	// Constructor
	std_total += BenchmarkTest(VectorConstructor<std::vector<int> >, "VectorConstructor", "std");
	ft_total += BenchmarkTest(VectorConstructor<ft::vector<int> >, "VectorConstructor", "ft");

	// Assign
	std_total += BenchmarkTest(VectorAssignment<std::vector<int> >, "VectorAssignment", "std");
	ft_total += BenchmarkTest(VectorAssignment<ft::vector<int> >, "VectorAssignment", "ft");

	// push_back
	std_total += BenchmarkTest(VectorPushback<std::vector<int> >, "VectorPushback", "std");
	ft_total += BenchmarkTest(VectorPushback<ft::vector<int> >, "VectorPushback", "ft");

	// pop_back
	std_total += BenchmarkTest(VectorPopback<std::vector<int> >, "VectorPopback", "std");
	ft_total += BenchmarkTest(VectorPopback<ft::vector<int> >, "VectorPopback", "ft");

	// iterating
	std_total += BenchmarkTest(VectorIterating<std::vector<int> >, "VectorIterating", "std");
	ft_total += BenchmarkTest(VectorIterating<ft::vector<int> >, "VectorIterating", "ft");

	// // clear
	std_total += BenchmarkTest(VectorClear<std::vector<int> >, "VectorClear", "std");
	ft_total += BenchmarkTest(VectorClear<ft::vector<int> >, "VectorClear", "ft");

	// swap
	std_total += BenchmarkTest(VectorSwap<std::vector<int> >, "VectorSwap", "std");
	ft_total += BenchmarkTest(VectorSwap<ft::vector<int> >, "VectorSwap", "ft");

	// resize
	std_total += BenchmarkTest(VectorResize<std::vector<int> >, "VectorResize", "std");
	ft_total += BenchmarkTest(VectorResize<ft::vector<int> >, "VectorResize", "ft");

	// insert
	std_total += BenchmarkTest(VectorInsert<std::vector<int> >, "VectorInsert", "std");
	ft_total += BenchmarkTest(VectorInsert<ft::vector<int> >, "VectorInsert", "ft");

	// erase
	std_total += BenchmarkTest(VectorErase<std::vector<int> >, "VectorErase", "std");
	ft_total += BenchmarkTest(VectorErase<ft::vector<int> >, "VectorErase", "ft");

	std::cout << std::endl;
	std::cout << "STD_TOTAL = " << std_total << std::endl;
	std::cout << " FT_TOTAL = " << ft_total << std::endl;
}

}

