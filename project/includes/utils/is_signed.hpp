#ifndef IS_SIGNED_HPP
# define IS_SIGNED_HPP

# include "reimplemented/is_integral.hpp"

namespace ft {

	namespace _base_detail {
	
	template <bool Condition>
	struct is_signed_base : public ft::false_type {};

	template <>
	struct is_signed_base<true> : public ft::true_type {};


	}

template <class T>
struct is_signed :
public ft::_base_detail::is_signed_base< (T(-1) < T(0)) > {};

}

#endif /* IS_SIGNED_HPP */
