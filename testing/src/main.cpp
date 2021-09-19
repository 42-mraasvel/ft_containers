#include <iostream>
#include "FakeIterator.hpp"
#include "FakeAllocator.hpp"

#include "containers/vector.hpp"
#include "containers/set.hpp"
#include "reimplemented/iterator_traits.hpp"
#include "reimplemented/allocator_traits.hpp"
#include "utils/is_allocator.hpp"
#include "utils/is_iterator.hpp"
#include "utils/is_same.hpp"
#include <vector>
#include <iterator>
#include <map>

/*
	typedef ptrdiff_t							difference_type;
	typedef T									value_type;
	typedef T*									pointer;
	typedef T&									reference;
	typedef std::random_access_iterator_tag		iterator_category;
*/

int main() {

	ft::set<int> s;

	std::cout << s.size() << std::endl;
	s.insert(s.end(), 1);
	std::cout << s.size() << std::endl;

	return 0;
}
