#ifndef ITERATOR_AVL_HPP
# define ITERATOR_AVL_HPP

# include "iterator.hpp"
# include "node_avl.hpp"

namespace ft {

template <typename T>
class IteratorAVL
	: public ft::iterator<ft::bidirectional_iterator_tag, T> {
public:
	typedef NodeAVL<T>* node_type;

	typedef ft::iterator<ft::bidirectional_iterator_tag, T> parent_t;
	typedef typename parent_t::reference reference;
	typedef const typename parent_t::reference const_reference;
	typedef typename parent_t::pointer pointer;
	typedef const typename parent_t::pointer const_pointer;

/* Constructors / Destructor */
public:
	IteratorAVL()
	: _ptr(NULL) {}
	IteratorAVL(const IteratorAVL& from)
	: _ptr(from._ptr) {}
	~IteratorAVL() {}

	IteratorAVL(const node_type node)
	: _ptr(node) {}

/* Operators */
	IteratorAVL& operator=(const IteratorAVL& rhs) {
		_ptr = rhs._ptr;
		return *this;
	}

/* Input */
	IteratorAVL& operator++() {
		_ptr = _ptr->next();
		return *this;
	}

	IteratorAVL operator++(int) {
		IteratorAVL temp(_ptr);
		_ptr = _ptr->next;
		return temp;
	}

	bool operator==(const IteratorAVL& rhs) {
		return _ptr == rhs._ptr;
	}

	bool operator!=(const IteratorAVL& rhs) {
		return !(*this == rhs);
	}

	reference operator*() {
		return _ptr->key;
	}

	const_reference operator*() const {
		return _ptr->key;
	}

	pointer operator->() {
		return &(_ptr->key);
	}

	const_pointer operator->() const {
		return &(_ptr->key);
	}

/* Bidirectional */
	IteratorAVL& operator--() {
		_ptr = _ptr->prev();
		return *this;
	}

	IteratorAVL& operator--(int) {
		IteratorAVL temp(_ptr);
		_ptr = _ptr->prev();
		return temp;
	}

/* Private Member Variables */
private:
	node_type _ptr;
};

}

#endif /* ITERATOR_AVL_HPP */
