#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
/*

Resources:

	https://www.cplusplus.com/reference/vector/vector/

*/

# include "utils.hpp"
# include "reverse_iterator.hpp"
# include "enable_if.hpp"
# include "is_integral.hpp"
# include "equal.hpp"
# include "lexicographical_compare.hpp"

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

	typedef pointer iterator;
	typedef const_pointer const_iterator;
	typedef ft::reverse_iterator<iterator> reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

	typedef typename iterator_traits<iterator>::difference_type difference_type;
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

	// Range: use template enable_if to prevent integrals from calling this
	template <class InputIterator>
	vector(InputIterator first, InputIterator last,
			const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = true)
	: _alloc(alloc), _capacity(0), _size(0), _table(NULL) {

		assign(first, last);
	}

	// Copy
	vector(const vector& x)
	: _alloc(x._alloc), _capacity(0), _size(0), _table(NULL) {
		*this = x;
	}

/* Destructor */
	~vector() {
		_deallocate();
	}

/* Assignment Operator */
	vector<value_type, allocator_type>& operator=(const vector<value_type>& x) {
		if (this == &x)
			return *this;

		clear();
		reserve(x.size());
		_size = x.size();
		ft::copy_uninitialized(x.begin(), x.end(), begin(), _alloc);
		return *this;
	}

/* Iterators! TODO */
	iterator begin() {
		return _table;
	}

	const_iterator begin() const {
		return _table;
	}

	iterator end() {
		return _table + size();
	}

	const_iterator end() const {
		return _table + size();
	}

	reverse_iterator rbegin() {
		return reverse_iterator(end());
	}

	const_reverse_iterator rbegin() const {
		return const_reverse_iterator(end());
	}

	reverse_iterator rend() {
		return reverse_iterator(begin());
	}

	const_reverse_iterator rend() const {
		return const_reverse_iterator(begin());
	}

/* Capacity */
	size_type size() const {
		return _size;
	}

	size_type max_size() const {
		return _alloc.max_size();
	}

	void resize(size_type n) {
		if (n < size()) {
			for (size_type i = size(); i > n; --i) {
				_alloc.destroy(_table + i);
			}
			_size = n;
			return;
		} else {
			reserve(ft::max(capacity() * 2, n));
			for (size_type i = 0; i < n; ++i ) {
				_alloc.construct(_table + size() + i);
			}
			// ft::construct_uninitialized(n, val, end(), _alloc);
			_size = n;
		}
	}

	void resize(size_type n, const value_type& val) {
		if (n < size()) {
			for (size_type i = size(); i > n; --i) {
				_alloc.destroy(_table + i);
			}
			_size = n;
			return;
		} else {
			reserve(ft::max(capacity() * 2, n));
			ft::construct_uninitialized(n, val, end(), _alloc);
			_size = n;
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

		pointer temp = _allocate(n);
		if (size() > 0)
		{
			ft::copy_uninitialized(begin(), end(), temp, _alloc);
			_deallocate();
		}
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
	template <class InputIterator>
	void assign(InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = true) {

		clear();
		size_type dist = ft::distance(first, last);
		reserve(dist);
		ft::copy_uninitialized(first, last, begin(), _alloc);
		_size = dist;
	}

	// Fill
	void assign(size_type n, const value_type& val) {
		clear();
		reserve(n);
		ft::construct_uninitialized(n, val, _table, _alloc);
		_size = n;
	}

	void push_back(const value_type& val) {
		_ensure_capacity();
		_alloc.construct(_table + _size, val);
		++_size;
	}

	void pop_back() {
		_alloc.destroy(_table + _size);
		--_size;
	}
	// Single Element
	iterator insert(iterator position, const value_type& val) {
		if (size() >= capacity())
		{
			size_type new_capacity = ft::max(capacity() * 2, size() + 1);
			pointer temp = _allocate(new_capacity);

			pointer next;
			next = ft::copy_uninitialized(begin(), position, temp, _alloc);
			*next = val;
			ft::copy_uninitialized(position, end(), next + 1, _alloc);

			_deallocate();
			_table = temp;
			_capacity = new_capacity;
			_size += 1;
			return next;
		}
		else {
			_alloc.construct(end(), back());
			if (position + 1 < end()) {
				ft::copy_backward(position, end() - 1, end());
			}
			*position = val;
			++_size;
			return position;
		}
	}

	// Fill
	void insert(iterator position, size_type n, const value_type& val) {
		if (size() + n > capacity()) {
			// reallocate and construct new table
			size_type new_capacity = ft::max(capacity() * 2, size() + n);
			pointer temp = _allocate(new_capacity);

			pointer next;
			next = ft::copy_uninitialized(begin(), position, temp, _alloc);
			next = ft::construct_uninitialized(n, val, next, _alloc);
			ft::copy_uninitialized(position, end(), next, _alloc);

			_deallocate();
			_table = temp;
			_capacity = new_capacity;
			_size += n;

		} else {

			ft::copy_uninitialized(end() - n, end(), end(), _alloc);
			ft::copy_backward(position, end() - n, end());

			// Assign fill to positoin
			for (size_type i = 0; i < n; ++i) {
				*position = val;
				++position;
			}
			_size += n;
		}
	}

	// Range
	template <class InputIterator>
	void insert (iterator position, InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = true) {
		// First we assume RandomAcessIterator type
		//	(should tag dispatch based on actual type)
		size_type n = last - first;

		if (size() + n > capacity()) {
			// Allocate new space
			size_type new_capacity = ft::max(capacity() * 2, size() + n);
			pointer temp = _allocate(new_capacity);

			pointer next;
			next = ft::copy_uninitialized(begin(), position, temp, _alloc);
			next = ft::copy_uninitialized(first, last, next, _alloc);
			ft::copy_uninitialized(position, end(), next, _alloc);

			_deallocate();
			_table = temp;
			_capacity = new_capacity;
			_size = size() + n;
		} else {
			// Copy into current space
			/*
				1. Initialize empty spots
				2. Backward copy filled spots
				3. Assign from iterators
			*/
			ft::copy_uninitialized(end() - n, end(), end(), _alloc);
			ft::copy_backward(position, end() - n, end());
			ft::copy(first, last, position);
			_size += n;
		}
	}

	iterator erase (iterator position) {
		ft::copy(position + 1, end(), position);
		_alloc.destroy(&back());
		_size -= 1;
		return position;
	}

	iterator erase (iterator first, iterator last) {
		size_type dist = ft::distance(first, last);
		ft::copy(last, end(), first);
		for (iterator it = end() - dist; it != end(); ++it) {
			_alloc.destroy(it);
		}
		_size -= dist;
		return last;
	}

	void swap(vector& x) {
		ft::swap(_alloc, x._alloc);
		ft::swap(_capacity, x._capacity);
		ft::swap(_size, x._size);
		ft::swap(_table, x._table);
	}

	void clear() {
		_destroy();
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

		reserve(ft::max(size_type(1), capacity() * 2));
	}

	pointer _allocate_dynamic(size_type n) {
		_alloc.allocate(ft::max(capacity() * 2, n));
	}

	pointer _allocate(size_type n) {
		return _alloc.allocate(n);
	}

	void _destroy() {
		if (!_table) {
			return;
		}

		for (size_type i = 0; i < size(); ++i) {
			_alloc.destroy(_table + i);
		}
	}

	void _deallocate() {
		if (!_table) {
			return;
		}
		_destroy();
		_alloc.deallocate(_table, capacity());
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
bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
	return !(lhs == rhs);
}

template <class T, class Alloc>
bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
	if (lhs.size() < rhs.size()) {
		return true;
	}

	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class T, class Alloc>
bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
	return !(rhs < lhs);
}

template <class T, class Alloc>
bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
	return rhs < lhs;
}

template <class T, class Alloc>
bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
	return !(lhs < rhs);
}


template <class T, class Alloc>
void swap(vector<T, Alloc>& x, vector<T, Alloc>& y) {
	x.swap(y);
}

}

#endif
