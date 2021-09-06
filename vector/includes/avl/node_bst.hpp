#ifndef NODE_BST_HPP
# define NODE_BST_HPP

namespace ft {

template <typename T, typename NodeType>
class NodeBST {
public:
	typedef T key_type;

public:
/* Constructors */
	NodeBST()
	: parent(NULL), left(NULL), right(NULL) {}

	NodeBST(const key_type& key)
	: key(key), parent(NULL), left(NULL), right(NULL) {}

	NodeBST(const NodeBST& node)
	: key(node.key), parent(node.parent), left(node.left), right(node.right) {}

	virtual ~NodeBST() {}

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
		}

		NodeType* current = parent;
		NodeType* prev = this;
		while (current) {
			if (prev == current->left) {
				return current;
			}
			prev = current;
			current = current->parent;
		}
		return NULL;
	}

	NodeType* prev() {
		if (left) {
			return _M_find_max(left);
		}

		NodeType* current = parent;
		NodeType* prev = this;
		while (current) {
			if (prev == current->right) {
				return current;
			}
			prev = current;
			current = current->parent;
		}
		return NULL;
	}

private:
/* Private Utility Member Functions */
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

/* Member Variables */
public:
	key_type key;
	NodeType* parent;
	NodeType* left;
	NodeType* right;

};

}


#endif /* NODE_BST_HPP */
