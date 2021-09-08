#ifndef ITERATOR_AVL_HPP
# define ITERATOR_AVL_HPP

# include "iterator.hpp"
# include "node_avl.hpp"

namespace ft {

struct EndNode {
public:
	EndNode() {}

private:

};

template <typename T>
class IteratorAVL
	: public ft::iterator<ft::bidirectional_iterator_tag, T> {
public:
	typedef NodeAVL<T>* node_type;
	typedef NodeAVL<const T>* const_node_type;

	typedef ft::iterator<ft::bidirectional_iterator_tag, T> parent_t;
	typedef typename parent_t::reference reference;
	typedef const typename parent_t::reference const_reference;
	typedef typename parent_t::pointer pointer;
	typedef const typename parent_t::pointer const_pointer;

	typedef IteratorAVL<const T> const_iterator;

/* Constructors / Destructor */
public:
	IteratorAVL()
	: _ptr(NULL), _max_ptr(NULL), _end_reached(false) {}
	IteratorAVL(const IteratorAVL& from)
	: _ptr(from._ptr), _max_ptr(from._max_ptr), _end_reached(from._end_reached) {}
	~IteratorAVL() {}

	IteratorAVL(const node_type node, const node_type* max_ptr)
	: _ptr(node), _max_ptr(max_ptr), _end_reached(false) {
		if (node == NULL && max_ptr != NULL)
			_end_reached = true;
	}

	IteratorAVL(const node_type node, const node_type* max_ptr, bool end)
	: _ptr(node), _max_ptr(max_ptr), _end_reached(end) {}

public:

/*

	******** TESTING PURPOSES ********

*/
	bool is_end() const {
		return _end_reached;
	}

	void* ptr() const {
		return _ptr;
	}

	const void* max_ptr() const {
		return _max_ptr;
	}

/* Operators */
	IteratorAVL& operator=(const IteratorAVL& rhs) {
		if (this == &rhs) {
			return *this;
		}
		_ptr = rhs._ptr;
		_max_ptr = rhs._max_ptr;
		_end_reached = rhs._end_reached;
		return *this;
	}

/* Input */
	IteratorAVL& operator++() {
		_ptr = _ptr->next();
		if (_ptr == NULL) {
			_end_reached = true;
		}
		return *this;
	}

	IteratorAVL operator++(int) {
		IteratorAVL temp(*this);
		_ptr = _ptr->next();
		if (_ptr == NULL) {
			_end_reached = true;
		}
		return temp;
	}

	bool operator==(const IteratorAVL& rhs) const {
		return _ptr == rhs._ptr && _end_reached == rhs._end_reached && _max_ptr == rhs._max_ptr;
	}

	bool operator!=(const IteratorAVL& rhs) const {
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
		if (_end_reached == true) {
			_ptr = *_max_ptr;
			_end_reached = false;
		} else {
			_ptr = _ptr->prev();
		}
		return *this;
	}

	IteratorAVL& operator--(int) {
		IteratorAVL temp(*this);
		if (_end_reached == true) {
			_ptr = *_max_ptr;
			_end_reached = false;
		} else {
			_ptr = _ptr->prev();
		}
		return temp;
	}

	void set_end() {
		_end_reached = true;
	}

	operator const_iterator() {
		return const_iterator(
			reinterpret_cast<const_node_type> (_ptr),
			reinterpret_cast<const const_node_type*> (_max_ptr),
			_end_reached
		);
	}

	node_type base() {
		return _ptr;
	}

/* Private Member Variables */
private:
	node_type _ptr;
	const node_type* _max_ptr;
	bool _end_reached;
};

}

#endif /* ITERATOR_AVL_HPP */
