#ifndef IS_SAME_HPP
# define IS_SAME_HPP

# include "reimplemented/is_integral.hpp"

namespace ft {

	namespace _base_detail {
	
	template <class T, class U>
	struct _is_same_base {
		static const bool value = false;
	};

	template <class T>
	struct _is_same_base<T, T> {
		static const bool value = true;
	};

	}

template <class T, class U>
struct is_same
: public _base_detail::_is_same_base<typename ft::remove_cv<T>::type, typename ft::remove_cv<U>::type> {};

}

#endif /* IS_SAME_HPP */
