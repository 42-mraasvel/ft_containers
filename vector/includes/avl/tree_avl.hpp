#ifndef TREE_AVL_HPP
# define TREE_AVL_HPP

# include "node_avl.hpp"

# include <cstddef>

namespace ft {

template <typename T, typename Compare, typename Alloc>
class TreeAVL {
/* Member Types */
public:
	typedef T															value_type;
	typedef size_t														size_type;
	typedef NodeAVL<T>													node_type;

	typedef Compare														value_compare;

	typedef Alloc														allocator_type;
	typedef typename allocator_type::template rebind<node_type>::other	allocator_node;

	typedef typename allocator_node::pointer		node_pointer;
	typedef typename allocator_node::const_pointer	const_node_pointer;
	typedef typename allocator_node::pointer		node_reference;
	typedef typename allocator_node::const_pointer	const_node_reference;

/*


************ TESTING PURPOSES, REMOVE ON TURNIN **********

*/
public:
	node_pointer root() {
		return _root;
	}

/* Constructors / Destructor */
private:
	TreeAVL()
	: _root(NULL), _size(0) {}
public:
	TreeAVL(const Compare& c)
	: _root(NULL), _compare(c), _size(0) {}
	TreeAVL(const TreeAVL& from) {}

	~TreeAVL() {}

/* Operators */
	TreeAVL& operator=(const TreeAVL& rhs) {
		return *this;
	}

/* Public Member Functions */
	node_pointer insert(const value_type& val) {
		return _M_insert(val);
	}

	void clear() {}

/* Private Member Functions */
private:
	node_pointer _M_new_node(const value_type& val) {
		node_pointer node = _alloc.allocate(1);
		_alloc.construct(node, node_type(val));
		return node;
	}

/* AVL Rotations */
	void _M_rotate_left(node_pointer x) {
		node_pointer y  = x->right;
		y->parent = x->parent;
		if (y->parent == NULL)
			_root = y;
		x->right = y->left;
		if (x->right)
			x->right->parent = x;
		x->parent = y;
		y->left = x;
		x->update_height();
		y->update_height();
	}

	void _M_rotate_right(node_pointer x) {
		node_pointer y = x->left;
		y->parent = x->parent;
		if (y->parent == NULL)
			_root = y;
		x->left = y->right;
		if (x->left)
			x->left->parent = x;
		x->parent = y;
		y->right = x;
		x->update_height();
		y->update_height();
	}

/* Private Member Variables */
private:
	node_pointer _root;
	allocator_node _alloc;
	value_compare _compare;
	size_type _size;

};

}


#endif /* TREE_AVL_HPP */
