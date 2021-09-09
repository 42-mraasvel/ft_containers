#include "header.hpp"
#include "GenIterator.hpp"
#include "is_integral.hpp"
#include "FakeAllocator.hpp"
#include "map.hpp"
#include <cassert>
#include <random>
#include <algorithm>
#include <map>

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

int main() {
	ft::map<int, char> alice;
	ft::map<int, char> eve;

	alice[1] = 'a';
	alice[2] = 'b';
	alice[3] = 'c';

	eve = alice;

	std::cout << eve.size() << std::endl;

	auto min = eve.min();
	auto max = eve.max();

	std::cout << "MIN: " << min->key.second << std::endl;
	std::cout << "MAX: " << max->key.second << std::endl;

	auto base = eve.root();

	std::cout << "** base ** " << std::endl;
	std::cout << base->key.second << std::endl;
	std::cout << base << std::endl;
	std::cout << base->left->parent->key.second << std::endl;
	std::cout << base->right->parent << std::endl;


	std::cout << std::endl;
	auto it = eve.begin();
	++it;

	return 0;
}
#endif /* CATCH_TEST_ENABLED */
