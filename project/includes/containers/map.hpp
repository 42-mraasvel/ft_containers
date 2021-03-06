#ifndef MAP_HPP
# define MAP_HPP

# include "utils/less.hpp"
# include "utils/is_allocator.hpp"
# include "utils/is_same.hpp"
# include "reimplemented/reverse_iterator.hpp"
# include "reimplemented/equal.hpp"
# include "reimplemented/enable_if.hpp"
# include "reimplemented/lexicographical_compare.hpp"
# include "red_black/tree_rb.hpp"

namespace ft {

template < class Key,
			class T,
			class Compare = ft::less<Key>,
			class Alloc = std::allocator<ft::pair<const Key, T> > >
class map {
/* Member Types */
public:
	class value_compare;

	typedef Key											key_type;
	typedef T											mapped_type;
	typedef ft::pair<const key_type, mapped_type>		value_type;
	typedef Compare										key_compare;
	typedef Alloc										allocator_type;

	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;

private:
	typedef TreeRB<value_type, value_compare, allocator_type>	tree_type;

public:
	typedef typename tree_type::iterator iterator;
	typedef typename tree_type::const_iterator const_iterator;
	typedef ft::reverse_iterator<iterator>			reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	typedef typename iterator_traits<iterator>::difference_type	difference_type;
	typedef size_t size_type;

public:
/* Constructors / Destructor */

	/* empty */
	explicit map(const key_compare& key = key_compare(),
				const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<ft::is_allocator<allocator_type>::value, bool>::type = true,
				typename ft::enable_if<ft::is_same<value_type, typename allocator_type::value_type>::value, bool>::type = true)
	: _tree(value_compare(key)), _alloc(alloc) {}

	/* range */
	template <class InputIterator>
	map(InputIterator first, InputIterator last,
		const key_compare& key = key_compare(),
		const allocator_type& alloc = allocator_type(),
		typename ft::enable_if<ft::is_iterator<InputIterator>::value, bool>::type = true,
		typename ft::enable_if<ft::is_allocator<allocator_type>::value, bool>::type = true,
		typename ft::enable_if<ft::is_same<value_type, typename allocator_type::value_type>::value, bool>::type = true)
	: _tree(value_compare(key)), _alloc(alloc) {
		insert(first, last);
	}

	/* copy */
	map(const map& x)
	: _tree(x._tree), _alloc(x._alloc) {}

	~map() {}

/* Operators */

	map& operator=(const map& rhs) {
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
		return _tree.size() == 0;
	}

	size_type size() const {
		return _tree.size();
	}
	
	size_type max_size() const {
		return _tree.max_size();
	}

/* Element Access */

	mapped_type& operator[](const key_type& k) {
		return insert(ft::make_pair(k, mapped_type())).first->second;
	}

/* Modifiers */

	/* single element */
	ft::pair<iterator, bool> insert(const value_type& val) {
		size_type old_size = size();
		iterator it = _tree.insert(val);
		return ft::make_pair(it, old_size != size());
	}

	/* with hint */
	iterator insert(iterator position, const value_type& val) {
		(void)position;
		return _tree.insert(val);
	}

	/* range */
	template <class InputIterator>
	void insert(InputIterator first, InputIterator last,
				typename ft::enable_if< ft::is_iterator<InputIterator>::value, bool>::type = true) {
		while (first != last) {
			_tree.insert(*first);
			++first;
		}
	}

	void erase(iterator position) {
		return _tree.erase(position);
	}

	size_type erase(const key_type& k) {
		size_type old_size = size();
		_tree.erase(find(k));
		return old_size - size();
	}

	void erase(iterator first, iterator last) {
		while (first != last) {
			_tree.erase(first++);
		}
	}

	void swap(map& x) {
		_tree.swap(x._tree);
	}

	void clear() {
		tree().clear();
	}


/* Observers */

	key_compare key_comp() const {
		return _tree.value_comp().comp_object();
	}

	value_compare value_comp() const {
		return _tree.value_comp();
	}

/* Operations */

	iterator find(const key_type& k) {
		return _tree.find(ft::make_pair(k, mapped_type()));
	}

	const_iterator find(const key_type& k) const {
		return _tree.find(ft::make_pair(k, mapped_type()));
	}

	size_type count(const key_type& k) const {
		return find(k) != end() ? 1 : 0;
	}

	iterator lower_bound(const key_type& k) {
		return _tree.lower_bound(ft::make_pair(k, mapped_type()));
	}

	const_iterator lower_bound(const key_type& k) const {
		return _tree.lower_bound(ft::make_pair(k, mapped_type()));
	}

	iterator upper_bound(const key_type& k) {
		return _tree.upper_bound(ft::make_pair(k, mapped_type()));
	}

	const_iterator upper_bound(const key_type& k) const {
		return _tree.upper_bound(ft::make_pair(k, mapped_type()));
	}

	ft::pair<iterator,iterator> equal_range(const key_type& k) {
		return _tree.equal_range(ft::make_pair(k, mapped_type()));
	}

	ft::pair<const_iterator,const_iterator> equal_range(const key_type& k) const {
		return _tree.equal_range(ft::make_pair(k, mapped_type()));
	}

/* Allocator */

	allocator_type get_allocator() const {
		return _alloc;
	}


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
	allocator_type _alloc;

};

/*
	value_compare nested class definition
*/
template <class Key, class T, class Compare, class Alloc>
class map<Key,T,Compare,Alloc>::value_compare : public ft::binary_function<Key, T, bool> {
private:
	value_compare() {}

protected:
	Compare comp;

public:
	value_compare (Compare c)
	: comp(c) {}

	value_compare(const value_compare& from)
	: comp(from.comp) {}

	value_compare& operator=(const value_compare& rhs) {
		if (this == &rhs)
			return *this;
		comp = rhs.comp;
		return *this;
	}

	Compare comp_object() const {
		return comp;
	}

	bool operator() (const value_type& x, const value_type& y) const {
		return comp(x.first, y.first);
	}
};

template <class Key, class T, class Compare, class Alloc>
void swap(map<Key, T, Compare, Alloc>& x, map<Key, T, Compare, Alloc>& y) {
	x.swap(y);
}

template <class Key, class T, class Compare, class Alloc>
bool operator==(const ft::map<Key, T, Compare ,Alloc>& lhs,
				const ft::map<Key, T, Compare, Alloc>& rhs) {
	if (lhs.size() != rhs.size()) {
		return false;
	}

	return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class Key, class T, class Compare, class Alloc>
bool operator!=(const ft::map<Key,T,Compare,Alloc>& lhs,
				const ft::map<Key,T,Compare,Alloc>& rhs) {
	return !(lhs == rhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator<( const ft::map<Key, T, Compare, Alloc>& lhs,
				const ft::map<Key, T, Compare, Alloc>& rhs) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class Key, class T, class Compare, class Alloc>
bool operator<=(const ft::map<Key, T, Compare, Alloc>& lhs,
				const ft::map<Key, T, Compare, Alloc>& rhs) {
	return !(rhs < lhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator>( const ft::map<Key, T, Compare, Alloc>& lhs,
				const ft::map<Key, T, Compare, Alloc>& rhs) {
	return rhs < lhs;
}

template <class Key, class T, class Compare, class Alloc>
bool operator>=(const ft::map<Key, T, Compare, Alloc>& lhs,
				const ft::map<Key, T, Compare, Alloc>& rhs) {
	return !(lhs < rhs);
}

}

#endif /* MAP_HPP */
