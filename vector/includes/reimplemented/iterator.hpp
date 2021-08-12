#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>
# include <iterator>

namespace ft {

/*
Importing iterator tags to ft namespace
*/
typedef std::input_iterator_tag input_iterator_tag;
typedef std::output_iterator_tag output_iterator_tag;
typedef std::forward_iterator_tag forward_iterator_tag;
typedef std::bidirectional_iterator_tag bidirectional_iterator_tag;
typedef std::random_access_iterator_tag random_access_iterator_tag;


/*
Iterator base class
*/
template <	class Category,
			class T,
			class Distance = ptrdiff_t,
			class Pointer = T*,
			class Reference = T&>
struct iterator {
	typedef T			value_type;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef Category	iterator_category;
};

}

#endif /* ITERATOR_HPP */
