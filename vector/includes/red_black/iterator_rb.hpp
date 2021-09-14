#ifndef ITERATOR_RB_HPP
# define ITERATOR_RB_HPP

# include "iterator.hpp"
# include "node_red_black.hpp"

namespace ft {

template <typename T>
class IteratorRB 
	: public ft::iterator<ft::bidirectional_iterator_tag, T> {

public:
	typedef NodeRB<T>* node_pointer;
	typedef NodeRB<const T>* const_node_pointer;

	typedef ft::iterator<ft::bidirectional_iterator_tag, T> parent_t;
	typedef typename parent_t::reference reference;
	typedef const typename parent_t::reference const_reference;
	typedef typename parent_t::pointer pointer;
	typedef const typename parent_t::pointer const_pointer;

	typedef IteratorRB<const T> const_iterator;

/* Constructors / Destructor */
public:
	IteratorRB()
	: _ptr(NULL), _max_ptr(NULL), _end_reached(false) {}
	IteratorRB(const IteratorRB& from)
	: _ptr(from._ptr), _max_ptr(from._max_ptr), _end_reached(from._end_reached) {}
	~IteratorRB() {}

	IteratorRB(const node_pointer node, const node_pointer* max_ptr)
	: _ptr(node), _max_ptr(max_ptr), _end_reached(false) {
		if (node == NULL && max_ptr != NULL)
			_end_reached = true;
	}

	IteratorRB(const node_pointer node, const node_pointer* max_ptr, bool end)
	: _ptr(node), _max_ptr(max_ptr), _end_reached(end) {}

public:
/* Operators */
	IteratorRB& operator=(const IteratorRB& rhs) {
		if (this == &rhs) {
			return *this;
		}
		_ptr = rhs._ptr;
		_max_ptr = rhs._max_ptr;
		_end_reached = rhs._end_reached;
		return *this;
	}

/* Input */
	IteratorRB& operator++() {
		_ptr = _ptr->next();
		if (_ptr == NULL) {
			_end_reached = true;
		}
		return *this;
	}

	IteratorRB operator++(int) {
		IteratorRB temp(*this);
		_ptr = _ptr->next();
		if (_ptr == NULL) {
			_end_reached = true;
		}
		return temp;
	}

	bool operator==(const IteratorRB& rhs) const {
		return _ptr == rhs._ptr && _end_reached == rhs._end_reached && _max_ptr == rhs._max_ptr;
	}

	bool operator!=(const IteratorRB& rhs) const {
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
	IteratorRB& operator--() {
		if (_end_reached == true) {
			_ptr = *_max_ptr;
			_end_reached = false;
		} else {
			_ptr = _ptr->prev();
		}
		return *this;
	}

	IteratorRB& operator--(int) {
		IteratorRB temp(*this);
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
			reinterpret_cast<const_node_pointer> (_ptr),
			reinterpret_cast<const const_node_pointer*> (_max_ptr),
			_end_reached
		);
	}

	node_pointer base() {
		return _ptr;
	}

/* Private Member Variables */
private:
	node_pointer _ptr;
	const node_pointer* _max_ptr;
	bool _end_reached;

};

}

#endif /* ITERATOR_RB_HPP */
