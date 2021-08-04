#ifndef VECTOR_HPP
# define VECTOR_HPP

/*

Resources:

	https://www.cplusplus.com/reference/vector/vector/

*/

# include <memory>
# include <cstddef>

namespace ft {

template <class T, class Allocator = std::allocator<T> >
class vector {
public:

/* Member Types */
	typedef T value_type;
	typedef Allocator allocator_type;
	typedef allocator_type::reference reference;
	typedef allocator_type::const_reference const_reference;
	typedef allocator_type::pointer pointer;
	typedef allocator_type::const_pointer const_pointer;

	// iterator
	// const_iterator
	// reverse_iterator
	// const_reverse_iterator

	typedef ptrdiff_t difference_type // iterator_traits<iterator>::difference_type
	typedef size_t size_type;

public:

/* Constructors */
	// Default
	explicit vector(const allocator_type& alloc = allocator_type());

	// fill
	explicit vector(size_type n, const value_type& val = value_type(),
					const allocator_type& alloc = allocator_type());
	// Range
	template <class InputIterator>
			vector(InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type());
	// Copy
	vector(const vector& x);

/* Destructor */
	~vector();

/* Iterators */
	// TODO

/* Capacity */
	size_type size() const;
	size_type max_size() const;
	void resize (size_type n, value_type val = value_type());
	size_type capacity() const;
	bool empty() const;
	void reserve (size_type n);

/* Element access */
	reference operator[] (size_type n);
	const_reference operator[] (size_type n) const;

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

	void push_back (const value_type& val);
	void pop_back();

	// Single Element
	iterator insert (iterator position, const value_type& val);

	// Fill
	void insert (iterator position, size_type n, const value_type& val);

	// Range
	template <class InputIterator>
	void insert (iterator position, InputIterator first, InputIterator last);

	// iterator erase (iterator position);
	// iterator erase (iterator first, iterator last);

	void swap (vector& x);

	void clear();

/* Allocator */
	allocator_type get_allocator() const;


private:

};

}

#endif
