#include "header.hpp"
#include "GenIterator.hpp"
#include "is_integral.hpp"
#include "FakeAllocator.hpp"
#include "red_black/node_red_black.hpp"
#include "map.hpp"
#include "set.hpp"
#include <cassert>
#include <random>
#include <algorithm>
#include <map>
#include <set>

template <typename C>
void PrintCapSize(const C& container) {
	std::cout << "\tSIZE(" << container.size() << ')' << std::endl;
	std::cout << "\tCAP(" << container.capacity() << ')' << std::endl;
}

template <typename C>
void PrintContainer(const C& container) {
	std::cout << "contains:";
	for (typename C::size_type i = 0; i < container.size(); ++i) {
		std::cout << ' ' << container[i];
	}
	std::cout << std::endl;
	PrintCapSize(container);
}

class IntIterator : public ft::iterator<ft::random_access_iterator_tag, int*> {};


#ifndef CATCH_TEST_ENABLED

# define N ft
# define DT Example
# define TAG input_iterator_tag

int TestAVL();

class Example {

public:
	Example(int x)
	: x(x) {}

	int getValue() const {
		return x;
	}

private:
	int x;
};

struct CompareExample
	: public ft::binary_function<Example, Example, bool> {
public:
	bool operator() (const Example& a, const Example& b) const {
		return a.getValue() < b.getValue();
	}
};

/*
input_iterator_tag;
output_iterator_tag;
forward_iterator_tag;
bidirectional_iterator_tag;
random_access_iterator_tag;
*/

void testRedBlack();

int main() {
	NS::set<int> s;

	s.insert(42);

	auto it = s.end();
	--it;
	std::cout << *it << std::endl;

	it = s.begin();

	std::cout << it.base() << ", " << s._tree._min_ptr << std::endl;

	++it;
	std::cout << it.base() << ", " << s._tree._end_ptr << std::endl;

	// auto rit = s.rend();
	// --rit;
	// std::cout << s._tree._end_ptr << std::endl;
	// std::cout << s._tree._min_ptr << std::endl;
	// std::cout << rit.base().base() << std::endl;
	// std::cout << *rit << std::endl;
	// REQUIRE(*rit == 42);
	// ++rit;
	// REQUIRE(rit == s.rend());
	return 0;
}
#endif /* CATCH_TEST_ENABLED */
