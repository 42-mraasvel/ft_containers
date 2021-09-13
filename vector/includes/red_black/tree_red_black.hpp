#ifndef TREE_RED_BLACK_HPP
# define TREE_RED_BLACK_HPP

# include "node_red_black.hpp"
# include "less.hpp"
# include "utils.hpp"

# include <memory>
# include <cstddef>

namespace ft {

template <typename T, typename Compare = ft::less<int>, typename Alloc = std::allocator<T> >
class TreeRB {
public:
/* Member Types */
	typedef NodeRB<T> node_type;
	typedef node_type* node_pointer;

	typedef Alloc allocator_type;
	typedef typename allocator_type::template rebind<node_type>::other	allocator_node;

	typedef Compare compare_type;

	typedef size_t size_type;

	typedef typename node_type::color_type color_type;

	static const color_type BLACK = node_type::BLACK;
	static const color_type RED = node_type::RED;

public:
	node_pointer base() {
		return _root;
	}

/* Constructors / Destructor */
public:
	TreeRB()
	: _root(NULL), _size(0) {}

	~TreeRB() {
		clear();
	}

	void insert(const T& val) {
		_M_insert(val);
	}

	size_type size() const {
		return _size;
	}

	void clear() {
		_M_clear(base());
	}

private:

/* Utilities */
	node_pointer _M_new_node(const T& val) {
		return _M_new_node(val, NULL);
	}

	node_pointer _M_new_node(const T& val, node_pointer parent) {
		node_pointer x = _alloc.allocate(1);
		_alloc.construct(x, node_type(val, parent));
		_added_node = x;
		return x;
	}

	void _M_destroy_node(node_pointer x) {
		_alloc.destroy(x);
		_alloc.deallocate(x, 1);
	}

	void _M_add_size(size_type n) {
		_size += n;
	}

	node_pointer _M_find_max(node_pointer x) {
		while (x->right) {
			x = x->right;
		}
		return x;
	}

	node_pointer _M_find_min(node_pointer x) {
		while (x->left) {
			x = x->left;
		}
		return x;
	}

/* Red-Black Utils */
	color_type _M_get_color(node_pointer x) {
		if (x == NULL) {
			return BLACK;
		}

		return x->color;
	}

/* Rotations */

	void _M_rotate_left(node_pointer x) {
		node_pointer y  = x->right;
		y->parent = x->parent;
		_M_change_parent_link(x, y);
		x->right = y->left;
		if (x->right) {
			x->right->parent = x;
		}
		x->parent = y;
		y->left = x;
	}

	void _M_rotate_right(node_pointer x) {
		node_pointer y = x->left;
		y->parent = x->parent;
		_M_change_parent_link(x, y);
		x->left = y->right;
		if (x->left) {
			x->left->parent = x;
		}
		x->parent = y;
		y->right = x;
	}

	void _M_change_parent_link(node_pointer x, node_pointer replacement) {
		node_pointer parent = x->parent;
		if (parent == NULL) {
			_root = replacement;
		} else if (parent->left == x) {
			parent->left = replacement;
		} else if (parent->right == x) {
			parent->right = replacement;
		}
		if (replacement) {
			replacement->parent = parent;
		}
	}


/* Insertion */
	node_pointer _M_insert(node_pointer x, const T& val) {

		if (x == NULL) {
			_M_add_size(1);
			_added_node = _M_new_node(val);
			return _added_node;
		}

		if (_compare(val, x->getValue())) {
			x->left = _M_insert(x->left, val);
		} else if (_compare(x->getValue(), val)) {
			x->right = _M_insert(x->right, val);
		} else {
			_added_node = x;
		}

		return x;
	}

	void _M_insert(const T& val) {
		node_pointer parent = _M_find_insert_position(val);

		if (parent == NULL) {
			_root = _M_new_node(val);
		} else if (_compare(val, parent->getValue())) {
			parent->left = _M_new_node(val, parent);
		} else if (_compare(parent->getValue(), val)) {
			parent->right = _M_new_node(val, parent);
		} else {
			return;
		}

		_M_add_size(1);
		_M_insert_fix_property(_added_node);
	}

	/* Return parent of insertion position or node if present */
	node_pointer _M_find_insert_position(const T& val) {
		node_pointer node = base();
		node_pointer parent = NULL;

		while (node) {
			parent = node;
			if (_compare(val, node->getValue())) {
				node = node->left;
			} else if (_compare(node->getValue(), val)) {
				node = node->right;
			} else {
				return node;
			}
		}

		return parent;
	}

/* Fixing RB property post-insertion */
	void _M_insert_fix_property(node_pointer x) {
		while (_M_get_color(x->parent) == RED) {

			if (_M_get_color(_M_get_uncle(x)) == RED) {
				_M_recolor_uncle(x);
				x = x->parent->parent;
			} else {

				x = _M_check_balance(x);
				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				if (x->parent == x->parent->parent->left) {
					_M_rotate_right(x->parent->parent);
				} else {
					_M_rotate_left(x->parent->parent);
				}
			}
		}
		_root->color = BLACK;
	}

	void _M_recolor_uncle(node_pointer x) {
		x->parent->color = BLACK;
		x->parent->parent->color = RED;
		_M_get_uncle(x)->color = BLACK;
	}

	node_pointer _M_check_balance(node_pointer x) {
		node_pointer parent = x->parent;
		if (parent == parent->parent->left && x == parent->right) {
			_M_rotate_left(parent);
		} else if (parent == parent->parent->right && x == parent->left) {
			_M_rotate_right(parent);
		} else {
			return x;
		}

		return parent;
	}

	node_pointer _M_get_uncle(node_pointer x) {
		if (x->parent == x->parent->parent->right) {
			return x->parent->parent->left;
		}

		return x->parent->parent->right;
	}

/* Node Deletion */
	void _M_delete_node(node_pointer x) {
		if (x->left && x->right) {
			node_pointer max = _M_find_max(x->right);
			_M_swap_node(x, max);
			_M_delete_node(x);
		} else if (x->left) {
			_M_transplant_node(x, x->left);
		} else if (x->right) {
			_M_transplant_node(x, x->right);
		} else {
			_M_transplant_node(x, NULL);
		}
	}

	void _M_transplant_node(node_pointer x, node_pointer y) {
		if (x->parent == NULL) {
			_root = y;
		} else if (x == x->parent->left) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}

		if (y != NULL) {
			y->parent = x->parent;
		}
	}

/* Node Swap Logic */
	void _M_swap_node(node_pointer x, node_pointer y) {
		if (x->parent == y)
			_M_swap(y, x);
		ft::swap(x->parent, y->parent);
		ft::swap(x->left, y->left);
		ft::swap(x->right, y->right);
		if (x->parent == x)
			_M_swap_adjust(x, y);
		_M_swap_update_parent_children(x, y);
	}

	void _M_swap_adjust(node_pointer x, node_pointer y) {
		if (y->left == y)
			y->left = x;
		else if (y->right == y)
			y->right = x;
		x->parent = y;
	}

	void _M_swap_update_parent_children(node_pointer x, node_pointer y)
	{
		_M_update_parent(x, y);
		_M_update_parent(y, x);
		_M_child_update_parent(x);
		_M_child_update_parent(y);
	}

	void _M_child_update_parent(node_pointer x)
	{
		if (x->left)
			x->left->parent = x;
		if (x->right)
			x->right->parent = x;
	}

	void _M_update_parent(node_pointer x, node_pointer y)
	{
		if (x->parent && x->parent != y)
		{
			if (x->parent->left == y)
				x->parent->left = x;
			else if (x->parent->right == y)
				x->parent->right = x;
		} else if (x->parent == NULL) {
			_root = x;
		}
	}


/* Capacity */
	void _M_clear(node_pointer x) {
		if (x == NULL) {
			return;
		}

		_M_clear(x->left);
		_M_clear(x->right);
		_M_destroy_node(x);
	}

private:
	node_pointer _root;
	allocator_node _alloc;
	size_type _size;
	compare_type _compare;

	node_pointer _added_node;

};

};

#endif  /* TREE_RED_BLACK_HPP */
