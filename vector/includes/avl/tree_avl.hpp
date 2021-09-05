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
		_M_insert(_root, val, NULL);
		return _last_node;
	}

	size_type size() const {
		return _size;
	}

	void clear() {}

/* Private Member Functions */
private:
	node_pointer _M_new_node(const value_type& val) const {
		node_pointer node = _alloc.allocate(1);
		_alloc.construct(node, node_type(val));
		return node;
	}

	node_pointer _M_new_node_update(const value_type& val, node_pointer parent) {
		_last_node = _M_new_node(val);
		_last_node->parent = parent;
		_M_size_add(1);
		return _last_node;
	}

/* Utils */

	void _M_size_add(size_type n) {
		_size += n;
	}

/*
AVL insertion
	Complexity: O(n log n)
	1. BST insert: O (n log n)
	2. Preserve AVL property: O(1)
	return: iterator to new node (or node if val was already present)
*/

	node_pointer _M_insert(node_pointer node, const value_type& val, node_pointer parent) {
		if (node == NULL)
			return _M_new_node_update(val, parent);

		if (node->key == val) {
			_last_node = node;
			return node;
		}

		if (value_comp(val, node->key))
			node->left = _M_insert(node->left, val, node);
		else
			node->right = _M_insert(node->right, val, node);

		node->update_height();
		_M_check_balance(node);
		return node;
	}


/*
AVL Rotations
	Rebalance tree using rotations when abs(balance) > 1
	Complexity: O(1) pointer swaps
Resource:
	https://www.youtube.com/watch?v=FNeL18KsWPc
*/
	void _M_check_balance(node_pointer node) {
		if (node->balance > 1)
		{
			if (node->left->balance < 0)
				_M_rotate_left(node->left);
			_M_rotate_right(node);
		}
		else if (node->balance < -1)
		{
			if (node->right->balance > 0)
				_M_rotate_right(node->right);
			_M_rotate_left(node);
		}
	}

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

	node_pointer _last_node;

};

}


#endif /* TREE_AVL_HPP */
