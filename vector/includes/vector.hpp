#ifndef VECTOR_HPP
# define VECTOR_HPP

/*

Resources:

	https://www.cplusplus.com/reference/vector/vector/

*/

# include "utils.hpp"

# include <memory> // std::allocator
# include <stdexcept> // std::out_of_range
# ifdef __linux__
# include <cstddef> // size_t
# endif /* __linux__ */

namespace ft {

template <class T, class Alloc = std::allocator<T> >
class vector {
public:

/* Member Types */
	typedef T value_type;
	typedef Alloc allocator_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;

	// iterator
	// const_iterator
	// reverse_iterator
	// const_reverse_iterator

	typedef ptrdiff_t difference_type; // iterator_traits<iterator>::difference_type
	typedef size_t size_type;

public:

/* Constructors */
	// Default
	explicit vector(const allocator_type& alloc = allocator_type())
	: _alloc(alloc), _capacity(0), _size(0), _table(NULL) {}

	// fill
	explicit vector(size_type n, const value_type& val = value_type(),
					const allocator_type& alloc = allocator_type())
	: _alloc(alloc), _capacity(n), _size(n) {
		_table = _alloc.allocate(n);
		for (size_type i = 0; i < size(); ++i) {
			_alloc.construct(_table + i, val);
		}
	}

	// Range: For some reason this one is called with: v(1, 2) (2 ints)??
	// template <class InputIterator>
	// vector(InputIterator first, InputIterator last,
	// 		const allocator_type& alloc = allocator_type()) {}

	// Copy
	vector(const vector& x)
	: _alloc(x._alloc), _capacity(0), _size(0), _table(NULL) {
		*this = x;
	}

/* Destructor */
	~vector() {
		for (size_type i = 0; i < size(); ++i) {
			_alloc.destroy(_table + i);
		}
		_alloc.deallocate(_table, capacity());
	}

/* Assignment Operator */
	vector<value_type, allocator_type>& operator=(const vector<value_type>& x) {
		if (this == &x)
			return *this;

		// Use the assign range function?
		clear();
		reserve(x.size());
		_size = x.size();
		for (size_type i = 0; i < _size; ++i)
			_alloc.construct(_table + i, x[i]);
		return *this;
	}

/* Iterators! TODO */
	value_type* begin() {
		return _table;
	}

	value_type* end() {
		return _table + size();
	}

/* Capacity */
	size_type size() const {
		return _size;
	}

	size_type max_size() const {
		return _alloc.max_size();
	}

	void resize (size_type n, value_type val = value_type()) {
		if (n < size()) {
			for (size_type i = size(); i > n; --i) {
				_alloc.destroy(_table + i);
			}
			_size = n;
			return;
		}

		if (capacity() * 2 < n) {
			reserve(n);
		}

		for (size_type i = size(); i < n; ++i) {
			push_back(val);
		}
	}

	size_type capacity() const {
		return _capacity;
	}

	bool empty() const {
		return size() == 0;
	}

	void reserve (size_type n) {
		if (n <= capacity()) {
			return;
		}

		pointer temp = _alloc.allocate(n);
		ft::copy(_table, _table + size(), temp);
		if (_table)
			_alloc.deallocate(_table, capacity());
		_capacity = n;
		_table = temp;
	}

/* Element access */
	reference operator[] (size_type n) {
		return _table[n];
	}

	const_reference operator[] (size_type n) const {
		return _table[n];
	}


	reference at(size_type n) {
		if (n >= _size) {
			throw std::out_of_range("vector");
		}
		return _table[n];
	}

	const_reference at(size_type n) const {
		if (n >= _size) {
			throw std::out_of_range("vector");
		}
		return _table[n];
	}

	reference front() {
		return _table[0];
	}

	const_reference front() const {
		return _table[0];
	}

	reference back() {
		return _table[_size - 1];
	}

	const_reference back() const {
		return _table[_size - 1];
	}

/* Modifiers */
	// Range
	// template <class InputIterator>
	// void assign(InputIterator first, InputIterator last) {
	// 	clear();
	// 	reserve(ft::distance(first, last));
	// 	ft::copy(first, last, _table);
	// }

	// Fill
	void assign(size_type n, const value_type& val) {
		clear();
		reserve(n);
		_size = n;
		for (size_type i = 0; i < n; ++i) {
			_alloc.construct(_table + i, val);
		}
	}

	void push_back(const value_type& val) {
		_ensure_capacity();
		_table[_size] = val;
		++_size;
	}

	void pop_back() {
		_alloc.destroy(_table + _size);
		--_size;
	}

	// Single Element
	// iterator insert (iterator position, const value_type& val);

	// Fill
	// void insert (iterator position, size_type n, const value_type& val);

	// Range
	// template <class InputIterator>
	// void insert (iterator position, InputIterator first, InputIterator last);

	// iterator erase (iterator position);
	// iterator erase (iterator first, iterator last);

	void swap(vector& x) {
		ft::swap(_alloc, x._alloc);
		ft::swap(_capacity, x._capacity);
		ft::swap(_size, x._size);
		ft::swap(_table, x._table);
	}

	void clear() {
		for (size_type i = 0; i < size(); ++i) {
			_alloc.destroy(_table + i);
		}
		_size = 0;
	}

/* Allocator */
	allocator_type get_allocator() const {
		return _alloc;
	}

private:
/* Extra Functions / Utilities */
	void _ensure_capacity() {
		if (size() < capacity()) {
			return;
		}

		if (capacity() == 0) {
			reserve(1);
		} else {
			reserve(capacity() * 2);
		}
	}


private:
/* Attributes */
	allocator_type _alloc;
	size_type _capacity;
	size_type _size;
	pointer _table;
};

/* Non-member function overloads */

template <class T, class Alloc>
bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
	if (lhs.size() != rhs.size()) {
		return false;
	}

	return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class T, class Alloc>
bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);

template <class T, class Alloc>
bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);

template <class T, class Alloc>
bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);

template <class T, class Alloc>
bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);

template <class T, class Alloc>
bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);


template <class T, class Alloc>
void swap (vector<T, Alloc>& x, vector<T, Alloc>& y) {
	x.swap(y);
}


}

#endif
