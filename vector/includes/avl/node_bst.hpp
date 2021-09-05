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
	: _parent(NULL), _left(NULL), _right(NULL) {}

	NodeBST(const T& key)
	: _key(key), _parent(NULL), _left(NULL), _right(NULL) {}

	NodeBST(const NodeBST& node)
	: _key(node.key()), _parent(node.parent()), _left(node.left()), _right(node.right()) {}

	virtual ~NodeBST() {}

/* Operators */
	NodeBST& operator=(const NodeBST& rhs) {
		if (this == &rhs)
			return *this;
		key() = rhs.parent();
		parent() = rhs.parent();
		left() = rhs.left();
		right() = rhs.right();
		return *this;
	}

/* Public Member Functions */
	NodeType* next() {
		if (right())
			return _M_find_min(right());

		NodeType* current = parent();
		NodeType* prev = this;
		while (current) {
			if (prev == current->left)
				return current;
			prev = current;
			current = current->parent();
		}
		return NULL;
	}

	NodeType* prev() {
		if (left())
			return _M_find_max(left());

		NodeType* current = parent();
		NodeType* prev = this;
		while (current) {
			if (prev == current->right)
				return current;
			prev = current;
			current = current->parent;
		}
		return NULL;
	}

/* Getters */
	key_type& key() {
		return _key;
	}

	const key_type& key() const {
		return _key;
	}

	NodeType*& parent() {
		return _parent;
	}

	const NodeType*& parent() const {
		return _parent;
	}

	NodeType*& left() {
		return _left;
	}

	const NodeType*& left() const {
		return _left;
	}

	NodeType*& right() {
		return _right;
	}

	const NodeType*& right() const {
		return _right;
	}

private:
/* Private Utility Member Functions */
	NodeType* _M_find_max(NodeType* node) {
		if (!node)
			return NULL;
		while (node->right)
			node = node->right;
		return node;
	}

	NodeType* _M_find_min(NodeType* node) {
		if (!node)
			return NULL;
		while (node->left)
			node = node->left;
		return node;
	}

/* Member Variables */
protected:
	key_type _key;
	NodeType* _parent;
	NodeType* _left;
	NodeType* _right;

};

}


#endif /* NODE_BST_HPP */
