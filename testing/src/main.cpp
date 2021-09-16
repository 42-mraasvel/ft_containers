#include <iostream>
#include "FakeIterator.hpp"
#include "FakeAllocator.hpp"

#include "containers/vector.hpp"
#include "reimplemented/iterator_traits.hpp"
#include <vector>
#include <iterator>

/*
	typedef ptrdiff_t							difference_type;
	typedef T									value_type;
	typedef T*									pointer;
	typedef T&									reference;
	typedef std::random_access_iterator_tag		iterator_category;
*/

template <typename T>
struct make_t {
	typedef void type;
};

template <typename T>
struct is_iterator {

	typedef void* valid[2];
	typedef void* invalid[1];


	template <typename U>
	static valid& test( typename make_t<typename U::difference_type>::type*,
						typename make_t<typename U::value_type>::type*,
						typename make_t<typename U::pointer>::type*,
						typename make_t<typename U::reference>::type*,
						typename make_t<typename U::iterator_category>::type*
	);
	template <typename>
	static invalid& test(...);

	static const bool value = sizeof(test<T>(0, 0, 0, 0, 0)) == sizeof(valid);
};

template <typename T>
struct is_iterator<T*> {
	static const bool value = true;
};

template <typename T>
struct is_iterator<const T*> {
	static const bool value = true;
};

int main() {

	std::cout << std::boolalpha;

	int table[] = {0, 1, 2, 3, 4};
	int size = sizeof(table) / sizeof(int);

	static std::vector<int> v {0, 1, 2, 3, 4};


	std::cout << is_iterator<int>::value << std::endl;
	std::cout << is_iterator<FakeIterator<int>>::value << std::endl;
	std::cout << is_iterator<std::vector<int>::iterator>::value << std::endl;
	std::cout << is_iterator<int*>::value << std::endl;


	return 0;
}
