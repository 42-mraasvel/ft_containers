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
		}

		if (capacity() * 2 < n) {
			reserve(n);
		} else {
			reserve(capacity() * 2);
		}

		for (size_type i = size(); i < n; ++i) {
			// _alloc.construct(_table + i, val);
			_alloc.construct(_table + i);
			++_size;
		}
	}

	void resize(size_type n, const value_type& val) {
		if (n < size()) {
			for (size_type i = size(); i > n; --i) {
				_alloc.destroy(_table + i);
			}
			_size = n;
			return;
		}

		if (capacity() * 2 < n) {
			reserve(n);
		} else {
			reserve(capacity() * 2);
		}

		for (size_type i = size(); i < n; ++i) {
			// _alloc.construct(_table + i, val);
			_alloc.construct(_table + i, val);
			++_size;
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
		size_type temp_size = size();
		if (size() > 0)
		{
			ft::copy(begin(), end(), temp, _alloc);
			clear();
			_size = temp_size;
			_alloc.deallocate(_table, capacity());
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
		_size = dist;
		for (size_type i = 0; i < dist; ++i) {
			_alloc.construct(_table + i, *first);
			++first;
		}
	}

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
		_alloc.construct(_table + _size, val);
		++_size;
	}

	void pop_back() {
		_alloc.destroy(_table + _size);
		--_size;
	}
	// Single Element
	iterator insert(iterator position, const value_type& val) {

	/*
		if (not_enough_capacity)
			reallocate_then_construct_new_table
		else
			construct_only_at_end_assign_rest
	*/

		if (size() >= capacity())
		{
			size_type new_capacity;
			size_type new_size = size() + 1;

			pointer temp;
			difference_type dist = position - begin();
			if (capacity() == 0) {
				temp = _alloc.allocate(1);
				new_capacity = 1;
			} else {
				temp = _alloc.allocate(capacity() * 2);
				new_capacity = capacity() * 2;
			}
			position = begin() + dist;

			/*
				1. Copy up to position
				2. Copy position
				3. Copy everything after position
			*/
			size_type i = 0;
			iterator it;

			for (it = begin(); it != position; ++it) {
				_alloc.construct(temp + i, *it);
				++i;
			}

			_alloc.construct(temp + i, val);
			++i;
			while (it != end()) {
				_alloc.construct(temp + i, *it);
				++it;
				++i;
			}
			clear();
			_alloc.deallocate(_table, capacity());
			_size = new_size;
			_capacity = new_capacity;
			_table = temp;
			return position;
		}
		else {
			reverse_iterator first = rbegin();
			reverse_iterator last(position);

			_alloc.construct(begin() + size(), back());

			while (first != last - 1) {
				*first = (first[1]);
				++first;
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
			size_type new_capacity;
			if (capacity() * 2 >= size() + n) {
				new_capacity = capacity() * 2;
			} else {
				new_capacity = size() + n;
			}

			pointer temp = _alloc.allocate(new_capacity);

			size_type i = 0;
			iterator it;
			for (it = begin(); it != position; ++it) {
				_alloc.construct(temp + i, *it);
				++i;
			}

			for (size_type j = 0; j < n; ++j) {
				_alloc.construct(temp + i, val);
				++i;
			}

			for (; it != end(); ++it) {
				_alloc.construct(temp + i, *it);
				++i;
			}

			size_type new_size = size() + n;
			clear();
			_alloc.deallocate(_table, capacity());
			_table = temp;
			_capacity = new_capacity;
			_size = new_size;
			return;

		} else {

			reverse_iterator input = rbegin();
			reverse_iterator output = rbegin() - n;

			// move table, construct at end and assign rest
			for (size_type i = 0; i < n; ++i) {
				_alloc.construct(&(*output), *input);
				++input;
				++output;
			}

			while (input.base() != position) {
				*output = *input;
				++input;
				++output;
			}

			for (size_type i = 0; i < n; ++i) {
				*output = val;
				++output;
			}

			while (input != rend()) {
				*output = *input;
				++input;
				++output;
			}
			_size = size() + n;
		}
	}

	// Range
	template <class InputIterator>
	void insert (iterator position, InputIterator first, InputIterator last) {}

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
void swap(vector<T, Alloc>& x, vector<T, Alloc>& y) {
	x.swap(y);
}


}

#endif
