#include "header.hpp"

template <typename C>
void PrintCapSize(const C& container) {
	std::cout << "\tSIZE(" << container.size() << ')' << std::endl;
	std::cout << "\tCAP(" << container.capacity() << ')' << std::endl;
	std::cout << std::endl;
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


class IntIterator : public ft::iterator<ft::random_access_iterator_tag, int*> {};


# define N ft

#ifndef CATCH_TEST_ENABLED
int main() {


	return 0;
}
#endif
