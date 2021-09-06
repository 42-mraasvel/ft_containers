#ifndef MAP_HPP
# define MAP_HPP

# include "pair.hpp"
# include "less.hpp"
# include "reverse_iterator.hpp"
# include "tree_avl.hpp"

# include <memory> // std::allocator

# ifdef __linux__
# include <cstddef> // size_t
# endif /* __linux__ */

namespace ft {

template < class Key,
			class T,
			class Compare = ft::less<Key>,
			class Alloc = std::allocator<ft::pair<const Key, T> > >
class map {
/* Member Types */
private:
	class value_comp;
public:

	typedef Key											key_type;
	typedef T											mapped_type;
	typedef ft::pair<const key_type, mapped_type>		value_type;
	typedef Compare										key_compare;
	typedef value_comp									value_compare;
	typedef Alloc										allocator_type;



	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;

private:
	typedef TreeAVL<value_type, value_comp, allocator_type>	tree_type;

public:
	typedef typename tree_type::iterator iterator;
	typedef typename tree_type::const_iterator const_iterator;
	typedef ft::reverse_iterator<iterator>			reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	// typedef iterator_traits<iterator>::difference_type	difference_type;
	typedef ptrdiff_t difference_type;
	typedef size_t size_type;


/*


************ TESTING PURPOSES, REMOVE ON TURNIN **********

*/
public:
	typename tree_type::node_pointer root() {
		return tree().root();
	}

	typename tree_type::node_pointer max() {
		return tree().max();
	}

	typename tree_type::node_pointer min() {
		return tree().min();
	}

public:
/* Constructors / Destructor */

	/* empty */
	explicit map(const key_compare& key = key_compare(),
				const allocator_type& alloc = allocator_type())
	: _tree(value_compare(key)) {
		(void)alloc;
	}

	/* range */
	template <class InputIterator>
	map(InputIterator first, InputIterator last,
		const key_compare& key = key_compare(),
		const allocator_type& alloc = allocator_type())
	: _tree(value_compare(key)) {
		while (first != last) {
			tree().insert(*first);
			++first;
		}
	}

	/* copy */
	map(const map& x) {}

	~map() {}

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

/* Capacity */

	bool empty() const {
		return _tree.size() == 0;
	}

	size_type size() const {
		return _tree.size();
	}
	
	size_type max_size() const {
		return _tree.max_size();
	}

/* Element Access */

/* Modifiers */

	/* single element */
	// ft::pair<iterator, bool> insert(const value_type& val) {}
	bool insert(const value_type& val) {
		size_type old_size = size();
		_tree.insert(val);
		return old_size != size();
	}

	/* with hint */
	// iterator insert(iterator position, const value_type& val) {}

	/* range */
	// template <class InputIterator>
	// void insert(InputIterator first, InputIterator last) {}

	// void erase(iterator position) {}

	// size_type erase(const key_type& k) {}

	// void erase(iterator first, iterator last) {}

	void swap(map& x) {}

	void clear() {
		tree().clear();
	}


/* Observers */

/* Operations */

/* Private Member Functions */
private:
	tree_type& tree() {
		return _tree;
	}

	const tree_type& tree() const {
		return _tree;
	}

/* Private Member Variables */
private:
	tree_type _tree;

};

/*
	value_compare nested class definition
*/
template <class Key, class T, class Compare, class Alloc>
class map<Key,T,Compare,Alloc>::value_comp : public ft::binary_function<Key, T, bool> {
private:
	value_comp() {}

protected:
	Compare comp;

public:
	value_comp (Compare c)
	: comp(c) {}

	value_comp(const value_comp& from)
	: comp(from.comp) {}

	value_comp& operator=(const value_comp& rhs) {
		if (this == &rhs)
			return *this;
		comp = rhs.comp;
		return *this;
	}

	bool operator() (const value_type& x, const value_type& y) const {
		return comp(x.first, y.first);
	}
};

}

#endif /* MAP_HPP */
