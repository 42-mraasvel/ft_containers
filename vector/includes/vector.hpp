#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
/*

Resources:

	https://www.cplusplus.com/reference/vector/vector/

*/

# include "utils.hpp"
# include "reverse_iterator.hpp"
# include "iterator_traits.hpp"
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

		_table = _allocate(n);
		_initialize_mem(_table, n, val);
	}

	// Range: use template enable_if to prevent integrals from calling this
	template <class InputIterator>
	vector(InputIterator first, InputIterator last,
			const allocator_type& alloc = allocator_type())
	: _alloc(alloc), _capacity(0), _size(0), _table(NULL) {
		_internal_constructor(first, last, _is_integral(first));
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
	vector& operator=(const vector& x) {
		if (this == &x)
			return *this;

		assign(x.begin(), x.end());
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

	void resize(size_type n, const value_type& val = value_type()) {
		if (n < size()) {
			// Destroy the tail n members
			for (size_type i = size(); i > n; --i) {
				_alloc.destroy(_table + i - 1);
			}
			_size = n;
		} else if (n > size()) {
			if (n > capacity()) {
				reserve(ft::max(capacity() * 2, n));
			}
			ft::construct_uninitialized(n - _size, val, end(), _alloc);
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
		if (size() > 0) {
			_initialize_mem(temp, begin(), end());
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
		return _table[size() - 1];
	}

	const_reference back() const {
		return _table[size() - 1];
	}

/* Modifiers */
	// Range
	template <class InputIterator>
	void assign(InputIterator first, InputIterator last) {
		_assign_dispatch(first, last);
	}

	// Fill
	void assign(size_type n, const value_type& val) {
		_assign_dispatch(n, val);
	}

	void push_back(const value_type& val) {
		_ensure_capacity();
		_alloc.construct(end(), val);
		++_size;
	}

	void pop_back() {
		_alloc.destroy(&back());
		--_size;
	}

	// Single Element
	iterator insert(iterator position, const value_type& val) {
		return _insert_dispatch(position, 1, val, ft::true_type());
	}

	// Fill
	void insert(iterator position, size_type n, const value_type& val) {
		_insert_dispatch(position, n, val, ft::true_type());
	}

	// Range
	template <class InputIterator>
	void insert(iterator position, InputIterator first, InputIterator last) {
		_insert_dispatch(position, first, last, ft::_is_integral(first));
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
		return first;
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
/* Internal Construction, Initialization Dispatching */

	/* Fill */
	void _internal_constructor(size_type n, const value_type& val = value_type(),
							ft::true_type integral = ft::true_type()) {
		_table = _allocate(n);
		_size = n;
		_capacity = n;
		_initialize_mem(_table, n, val);
	}

	/* Range Constructors */
	template <class InputIterator>
	void _internal_constructor(InputIterator first, InputIterator last,
							ft::false_type integral = ft::false_type()) {
		/* Iterator Tag Dispatch */
		_range_construct_dispatch(first, last, ft::_iterator_category(first));
	}

	template <class InputIterator>
	void _range_construct_dispatch(InputIterator first, InputIterator last,
									ft::input_iterator_tag tag) {
		_push_back_range(first, last);
	}

	template <class ForwardIterator>
	void _range_construct_dispatch(ForwardIterator first, ForwardIterator last,
									ft::forward_iterator_tag tag) {
		size_type n = ft::distance(first, last);
		_table = _allocate(n);
		_capacity = n;
		_initialize_mem(_table, first, last);
		_size = n;
	}

/* Assign Dispatching */

	void _assign_dispatch(size_type n, const value_type& val) {
		_assign_fill(n, val);
	}

	template <class InputIterator>
	void _assign_dispatch(InputIterator first, InputIterator last, \
	typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = true) {
		_assign_range(first, last, ft::_iterator_category(first));
	}

	void _assign_fill(size_type n, const value_type& val) {
		clear();
		reserve(n);
		_initialize_mem(_table, n, val);
		_size = n;
	}

	template <class InputIterator>
	void _assign_range(InputIterator first, InputIterator last,
						ft::input_iterator_tag tag) {
		clear();
		_push_back_range(first, last);
	}

	template <class ForwardIterator>
	void _assign_range(ForwardIterator first, ForwardIterator last,
						ft::forward_iterator_tag tag) {
		clear();
		size_type dist = static_cast<size_type> (ft::distance(first, last));
		reserve(dist);
		_initialize_mem(_table, first, last);
		_size = dist;
	}

/* Insert Dispatching */

	iterator _insert_dispatch(iterator position, size_type n,
							const value_type& val, ft::true_type integral) {
		return _insert_fill(position, n, val);
	}

	template <class InputIterator>
	iterator _insert_dispatch(iterator position, InputIterator first,
							InputIterator last, ft::false_type integral) {
		return _insert_range(position, first, last, ft::_iterator_category(first));
	}

	iterator _insert_fill(iterator position, size_type n, const value_type& val) {
		if (size() + n > capacity()) {
			return _insert_fill_resize(position, n, val);
		} else {
			return _insert_fill_relocate(position, n , val);
		}
	}

	iterator _insert_fill_resize(iterator position, size_type n, const value_type& val) {

		const size_type new_cap = ft::max(capacity() * 2, size() + n);
		const difference_type dist = position - begin();

		pointer temp = _allocate(new_cap);
		_initialize_mem(temp, begin(), position);
		_initialize_mem(temp + dist, n, val);
		_initialize_mem(temp + dist + n, position, end());
		_replace_mem(temp, new_cap, size() + n);
		return begin() + dist;
	}

	iterator _insert_fill_relocate(iterator position, size_type n, const value_type& val) {
		if (position == end()) {
			_initialize_mem(end(), n, val);
		} else if (position + n < end()) {
			// CASE: values inserted go below initialized memory
			_initialize_mem(end(), end() - n, end());
			ft::copy_backward(position, end() - n, end());
			_copy_fill(position, n, val);
		} else {
			// CASE: values inserted go beyond initialized memory
			const difference_type dist = end() - position;
			_initialize_mem_backward(end() + n, position, end());
			_initialize_mem(end(), n - dist, val);
			_copy_fill(position, dist, val);
		}
		_size += n;
		return position;
	}

	template <class InputIterator>
	iterator _insert_range(iterator position, InputIterator first, InputIterator last,
							ft::input_iterator_tag tag) {
		/* Since InputIterators can only be iterated once, we need to allocate dynamically */
		const difference_type dist = position - begin();
		const size_type old_size = size();
		const size_type old_cap = capacity();

		pointer temp = _table;
		_table = _allocate(capacity());
		_initialize_mem(_table, temp, position);
		_size = dist;
		_push_back_range(first, last);
		_push_back_range(position, temp + old_size);
		_destroy_range(temp, temp + old_size);
		_alloc.deallocate(temp, old_cap);
		return position;
	}

	template <class ForwardIterator>
	iterator _insert_range(iterator position, ForwardIterator first, ForwardIterator last,
							ft::forward_iterator_tag tag) {

		const difference_type n = ft::distance(first, last);

		if (size() + n > capacity()) {
			return _insert_range_resize_forward(position, first, last, n);
		} else {
			return _insert_range_relocate_forward(position, first, last, n);
		}
	}

	template <class ForwardIterator>
	iterator _insert_range_resize_forward(iterator position, ForwardIterator first,
											ForwardIterator last, size_type n) {
		const size_type dist = position - begin();
		const size_type new_cap = ft::max(capacity() * 2, size() + n);

		pointer temp = _allocate(new_cap);
		_initialize_mem(temp, begin(), position);
		_initialize_mem(temp + dist, first, last);
		_initialize_mem(temp + dist + n, position, end());
		_replace_mem(temp, new_cap, size() + n);
		return begin() + dist;
	}

	template <class ForwardIterator>
	iterator _insert_range_relocate_forward(iterator position, ForwardIterator first,
											ForwardIterator last, size_type n) {
		if (position == end()) {
			_initialize_mem(end(), first, last);
		} else if (position + n < end()) {
			// CASE: values inserted go below initialized memory
			_initialize_mem(end(), end() - n, end());
			ft::copy_backward(position, end() - n, end());
			ft::copy(first, last, position);
		} else {
			// CASE: values inserted go beyond initialized memory
			const difference_type dist = end() - position;
			_initialize_mem_backward(end() + n, position, end());
			_initialize_mem(end(), first + dist, last);
			ft::copy(first, last - dist, position);
		}
		_size += n;
		return position;
	}

/* Extra Functions / Utilities */
	void _ensure_capacity() {
		if (size() < capacity()) {
			return;
		}

		reserve(ft::max(size_type(1), capacity() * 2));
	}

	void _replace_mem(pointer new_table, size_type new_cap, size_type new_size) {
		_deallocate();
		_table = new_table;
		_size = new_size;
		_capacity = new_cap;
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
		_table = NULL;
		_capacity = 0;
	}

	void _initialize_mem(pointer dest, size_type n, const value_type& val) {
		for (size_type i = 0; i < n; ++i) {
			_alloc.construct(dest + i, val);
		}
	}

	template <class InputIterator>
	void _initialize_mem(pointer dest, InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = true) {
		while (first != last) {
			_alloc.construct(dest, *first);
			++first;
			++dest;
		}
	}

	template <class InputIterator>
	void _initialize_mem_backward(pointer dest, InputIterator first, InputIterator last) {
		while (last != first) {
			--last;
			--dest;
			_alloc.construct(dest, *last);
		}
	}

	void _copy_fill(pointer dest, size_type n, const value_type& val) {
		for (size_type i = 0; i < n; ++i) {
			dest[i] = val;
		}
	}

	template <class InputIterator>
	void _push_back_range(InputIterator first, InputIterator last) {
		while (first != last) {
			push_back(*first);
			++first;
		}
	}

	void _destroy_range(pointer first, pointer last) {
		while (first != last) {
			_alloc.destroy(first);
			++first;
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
bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
	return !(lhs == rhs);
}

template <class T, class Alloc>
bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
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