#include "header.hpp"
#include "GenIterator.hpp"
#include "is_integral.hpp"

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
	std::cout << '$' << std::endl;
	PrintCapSize(container);
}

class Example
{
public:
	Example() {
		n = total++;
		std::cout << "Constructor: " << n << std::endl;
	}

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

# define N ft

#ifndef CATCH_TEST_ENABLED
int main() {


	N::vector<int> v(10);
	N::vector<int> v2(10);

	v.push_back(1);
	v2.push_back(1);
	PrintContainer(v);

	std::cout << std::boolalpha;
	std::cout << (v <= v2) << std::endl;
	return 0;
}
#endif
