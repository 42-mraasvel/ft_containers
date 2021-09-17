#ifndef DISTANCE_HPP
# define DISTANCE_HPP

# include "reimplemented/iterator_traits.hpp"
# include "utils/is_iterator.hpp"

namespace ft {

	namespace _base_detail {

	/* Distance specialization/optimization based on iteratir category */

	template <class InputIterator>
	ptrdiff_t _distance_base(InputIterator first, InputIterator last,
							ft::input_iterator_tag) {
		ptrdiff_t d = 0;

		while (first != last) {
			++d;
			++first;
		}
		return d;
	}

	template <class RandomAccessIterator>
	ptrdiff_t _distance_base(RandomAccessIterator first, RandomAccessIterator last,
							ft::random_access_iterator_tag) {
		return last - first;
	}

	}

template <class InputIterator>
ptrdiff_t distance(InputIterator first, InputIterator last,
					typename ft::enable_if<ft::is_iterator<InputIterator>::value, bool>::type = true) {
	return _base_detail::_distance_base(first, last, _iterator_category(first));
}

}

#endif /* DISTANCE_HPP */
