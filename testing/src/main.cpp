#include <iostream>
#include "FakeIterator.hpp"
#include "FakeAllocator.hpp"

#include "containers/vector.hpp"
#include "reimplemented/iterator_traits.hpp"
#include "reimplemented/allocator_traits.hpp"
#include "utils/is_allocator.hpp"
#include "utils/is_iterator.hpp"
#include "utils/is_same.hpp"
#include <vector>
#include <iterator>

/*
	typedef ptrdiff_t							difference_type;
	typedef T									value_type;
	typedef T*									pointer;
	typedef T&									reference;
	typedef std::random_access_iterator_tag		iterator_category;
*/

int main() {

	std::cout << std::boolalpha;

	int table[] = {0, 1, 2, 3, 4};
	int size = sizeof(table) / sizeof(int);
	bool table2[] = {true, false, false, true, true};

	ft::vector<int, std::allocator<int> > v;

	FakeIterator<int> it(table);
	FakeIterator<int> ite(table + size);
	FakeIterator<bool> it2(table2);
	ft::lexicographical_compare(it, ite, it2, it2 + sizeof(table2) / sizeof(bool));


	return 0;
}
