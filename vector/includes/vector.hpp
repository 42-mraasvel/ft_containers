#ifndef VECTOR_HPP
# define VECTOR_HPP

/*

Resources:

	https://www.cplusplus.com/reference/vector/vector/

*/

# include "utils.hpp"

# include <memory> // std::allocator
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

		// Construct all values using _alloc.construct(_table[i], val);
		for (size_type i = 0; i < size(); ++i) {
			_alloc.construct(_table + i, val);
		}
	}

	// Range: For some reason this one is called with: v(1, 2) (2 ints)??
	// template <class InputIterator>
	// vector(InputIterator first, InputIterator last,
	// 		const allocator_type& alloc = allocator_type()) {}
	// Copy
	vector(const vector& x);

/* Destructor */
	~vector() {
		for (size_type i = 0; i < size(); ++i) {
			_alloc.destroy(_table + i);
		}
		_alloc.deallocate(_table, capacity());
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

	void resize (size_type n, value_type val = value_type());

	size_type capacity() const {
		return _capacity;
	}

	bool empty() const {
		return size() == 0;
	}

	void reserve (size_type n);

/* Element access */
	reference operator[] (size_type n) {
		return _table[n];
	}

	const_reference operator[] (size_type n) const {
		return _table[n];
	}


	reference at(size_type n);
	const_reference at(size_type n) const;

	reference front();
	const_reference front() const;

	reference back();
	const_reference back() const;

/* Modifiers */
	// Range
	template <class InputIterator>
	void assign (InputIterator first, InputIterator last);

	// Fill
	void assign (size_type n, const value_type& val);

	void push_back (const value_type& val) {
		_table[_size++] = val;
	}

	void pop_back() {
		if (size() == 0)
			return;
		_alloc.destroy(_table[_size--]);
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

	void swap (vector& x);

	void clear();

/* Allocator */
	allocator_type get_allocator() const;


private:

	allocator_type _alloc;
	size_type _capacity;
	size_type _size;
	pointer _table;

};

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

}

#endif
