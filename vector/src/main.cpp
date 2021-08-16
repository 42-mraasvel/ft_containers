#include "header.hpp"
#include "GenIterator.hpp"
#include "is_integral.hpp"
#include "FakeAllocator.hpp"

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

class Example
{
public:
	Example() {
		n = total++;
		std::cout << "Constructor: " << n << std::endl;
	}

	Example(int n)
	: n(n) {}

	Example(const Example& from) {
		n = from.n;
		std::cout << "Copy Constructor: " << n << std::endl;
	}

	~Example() {
		std::cout << "Destructor: " << n << std::endl;
	}

	Example& operator=(const Example& rhs) {
		n = rhs.n;
		std::cout << "Assignment: " << n << std::endl;
		return *this;
	}

	static int total;

	int n;

};

std::ostream& operator<<(std::ostream& out, const Example& e) {
	out << e.n;
	return out;
}

int Example::total = 0;

class IntIterator : public ft::iterator<ft::random_access_iterator_tag, int*> {};


#ifndef CATCH_TEST_ENABLED

# ifndef N
# define N ft
# define DT Example
# endif

/*
input_iterator_tag;
output_iterator_tag;
forward_iterator_tag;
bidirectional_iterator_tag;
random_access_iterator_tag;
*/

int main() {

	const int size = 5;
	DT table[size]{};
	std::cout << std::endl;

	GenIterator<ft::random_access_iterator_tag, DT> it = table;
	GenIterator<ft::random_access_iterator_tag, DT> ite = table + size;

	N::vector<DT> v;

	v.push_back(Example(1));

	v.pop_back();

	PrintContainer(v);
	std::cout << std::endl;
	return 0;
}
#endif
