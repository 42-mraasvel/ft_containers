#ifndef NODE_BST_HPP
# define NODE_BST_HPP

namespace ft {

template <typename T, typename NodeType>
class NodeBST {
public:
	typedef T key_type;
	typedef NodeType* node_pointer;

public:
/* Constructors */
	NodeBST()
	: parent(NULL), left(NULL), right(NULL) {}

	NodeBST(const key_type& key)
	: key(key), parent(NULL), left(NULL), right(NULL) {}

	NodeBST(const NodeBST& node)
	: key(node.key), parent(node.parent), left(node.left), right(node.right) {}

	virtual ~NodeBST() {}

public:
/* Operators */
	NodeBST& operator=(const NodeBST& rhs) {
		if (this == &rhs)
			return *this;
		key = rhs.parent;
		parent = rhs.parent;
		left = rhs.left;
		right = rhs.right;
		return *this;
	}

/* Public Member Functions */
	NodeType* next() {
		if (right) {
			return _M_find_min(right);
		} else if (parent && parent->left == static_cast<void*>(this)) {
			return parent;
		}
		return _M_next_node(parent);
	}

	const NodeType* next() const {
		if (right) {
			return _M_find_min(right);
		} else if (parent && parent->left == static_cast<void*>(this)) {
			return parent;
		}
		return _M_next_node(parent);
	}

	NodeType* prev() {
		if (left) {
			return _M_find_max(left);
		} else if (parent && parent->right == static_cast<void*>(this)) {
			return parent;
		}
		return _M_prev_node(parent);
	}

	const NodeType* prev() const {
		if (left) {
			return _M_find_max(left);
		} else if (parent && parent->right == static_cast<void *>(this)) {
			return parent;
		}
		return _M_prev_node(parent);
	}

	static void swap(NodeType* a, NodeType* b) {
		_M_swap(a, b);
	}

private:
/* Private Utility Member Functions */

	static NodeType* _M_next_node(NodeType* node) {
		const NodeType* prev = NULL;
		while (node) {
			if (_M_node_equal(node->left, prev)) {
				return node;
			}
			prev = node;
			node = node->parent;
		}
		return NULL;
	}

	static NodeType* _M_prev_node(NodeType* node) {
		const NodeType* prev = NULL;
		while (node) {
			if (_M_node_equal(node->right, prev)) {
				return node;
			}
			prev = node;
			node = node->parent;
		}
		return NULL;
	}

	static bool _M_node_equal(const NodeType* a, const NodeType* b) {
		return a == b && a != NULL;
	}


	static NodeType* _M_find_max(NodeType* node) {
		if (!node) {
			return NULL;
		}
		while (node->right) {
			node = node->right;
		}
		return node;
	}

	static NodeType* _M_find_min(NodeType* node) {
		if (!node) {
			return NULL;
		}
		while (node->left) {
			node = node->left;
		}
		return node;
	}

/*
Node Swapping
*/
	static void _M_swap(NodeType* x, NodeType* y) {
		if (x->parent == y)
			_M_swap(y, x);
		ft::swap(x->parent, y->parent);
		ft::swap(x->left, y->left);
		ft::swap(x->right, y->right);
		if (x->parent == x)
			_M_swap_adjust(x, y);
		_M_swap_update_parent_children(x, y);
	}

	static void _M_swap_adjust(NodeType* x, NodeType* y) {
		if (y->left == y)
			y->left = x;
		else if (y->right == y)
			y->right = x;
		x->parent = y;
	}

	static void _M_swap_update_parent_children(NodeType* x, NodeType* y)
	{
		_M_update_parent(x, y);
		_M_update_parent(y, x);
		_M_child_update_parent(x);
		_M_child_update_parent(y);
	}

	static void _M_child_update_parent(NodeType* x)
	{
		if (x->left)
			x->left->parent = x;
		if (x->right)
			x->right->parent = x;
	}

	static void _M_update_parent(NodeType* x, NodeType* y)
	{
		if (x->parent && x->parent != y)
		{
			if (x->parent->left == y)
				x->parent->left = x;
			else if (x->parent->right == y)
				x->parent->right = x;
		}
	}

/* Member Variables */
public:
	key_type key;
	NodeType* parent;
	NodeType* left;
	NodeType* right;

};

}


#endif /* NODE_BST_HPP */
