#ifndef UTILS_HPP
# define UTILS_HPP

# include <cstddef>

namespace ft {

template <class InputIterator>
ptrdiff_t distance(InputIterator first, InputIterator last) {
	ptrdiff_t d(0);
	while (first != last) {
		++d;
		++first;
	}
	return d;
}

}


#endif /*  UTILS_HPP */
