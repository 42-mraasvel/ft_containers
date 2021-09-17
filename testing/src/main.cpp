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
#include <map>

/*
	typedef ptrdiff_t							difference_type;
	typedef T									value_type;
	typedef T*									pointer;
	typedef T&									reference;
	typedef std::random_access_iterator_tag		iterator_category;
*/

int main() {

	std::multimap<int, int> m;

	m.insert(std::make_pair(1, 42));
	m.insert(std::make_pair(1, 69));

	auto it = m.find(1);

	std::cout << it->second << std::endl;

	return 0;
}
