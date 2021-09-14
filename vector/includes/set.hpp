#ifndef SET_HPP
# define SET_HPP

# include "less.hpp"
# include "red_black/tree_red_black.hpp"
# include "reverse_iterator.hpp"
# include "pair.hpp"

# include <cstddef> // size_t
# include <memory> // std::allocator

namespace ft {

template <class T,
		class Compare = ft::less<T>,
		class Alloc = std::allocator<T> >
class set {

private:
	typedef ft::TreeRB<T, Compare, Alloc> tree_type;
public:
/* Public Member Types */
	typedef T key_type;
	typedef T value_type;
	typedef Compare key_compare;
	typedef Compare value_compare;
	typedef Alloc allocator_type;

	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;

	/* Iterators */

	typedef typename tree_type::iterator iterator;
	typedef typename tree_type::const_iterator const_iterator;

	typedef ft::reverse_iterator<iterator> reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

	// typedef ft::iterator_traits<iterator>::difference_type difference_type;
	typedef ptrdiff_t difference_type;
	typedef size_t size_type;

public:
/* Public Member Functions */

/* Constructors/Destructor */
	explicit set(const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
	: _tree(comp) {
		(void)alloc;
	}

	template <class InputIterator>
	set(InputIterator first, InputIterator last,
		const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type())
	: _tree(comp) {
		(void)alloc;
		while (first != last) {
			// insert(*first);
			++first;
		}
	}

	set(const set& x)
	: _tree(x._tree) {}

	~set() {}

/* Operators */
	set& operator=(const set& rhs) {
		_tree = rhs._tree;
		return *this;
	}

/* Iterators */
	iterator begin() {
		return _tree.begin();
	}

	const_iterator begin() const {
		return _tree.begin();
	}

	iterator end() {
		return _tree.end();
	}

	const_iterator end() const {
		return _tree.end();
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
	bool empty() const {
		return size() == 0;
	}

	size_type size() const {
		return _tree.size();
	}

	size_type max_size() const {
		return _tree.max_size();
	}

/* Modifiers */
	ft::pair<iterator, bool> insert(const value_type& val) {
		size_type old_size = size();
		iterator it = _tree.insert(val);
		return ft::make_pair(it, old_size > size());
	}

	iterator insert (iterator position, const value_type& val) {
		return _tree.insert(position, val);
	}

	template <class InputIterator>
	void insert(InputIterator first, InputIterator last) {
		while (first != last) {
			_tree.insert(*first);
			++first;
		}
	}


private:
/* Private Member Variables */
	tree_type _tree;
};

}

#endif /* SET_HPP */
