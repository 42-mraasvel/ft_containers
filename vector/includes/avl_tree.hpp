#ifndef AVL_TREE_HPP
# define AVL_TREE_HPP

#include "less.hpp"
#include "utils.hpp"

#include <iostream>
#include <iomanip>

namespace ft
{

template <typename T, typename Compare = ft::less<T> >
class AvlTree
{
public:
	typedef T value_type;
	typedef Compare compare_type;
public:

	struct Node
	{
		Node()
		: left(NULL), right(NULL), parent(NULL), balance(0), height(0) {}
		Node(const T& key)
		: key(key), left(NULL), right(NULL), parent(NULL), balance(0), height(0) {}
		Node(const T& key, Node* parent)
		: key(key), left(NULL), right(NULL), parent(parent), balance(0), height(0) {}
		Node (const Node& from)
		: key(from.key), left(NULL), right(NULL), parent(NULL), balance(0), height(0)
		{
			*this = from;
		}
	
		~Node() {}

		Node& operator=(const Node& rhs)
		{
			if (this == &rhs)
				return *this;
			key = rhs.key;
			left = rhs.left;
			right = rhs.right;
			parent = rhs.parent;
			balance = rhs.balance;
			height = rhs.height;
			return *this;
		}

		T key;
		Node* left;
		Node* right;
		Node* parent;
		int balance;
		int height;
	};

	Node* _root;
	compare_type _compare;
	std::allocator<Node> _alloc;

public:

	AvlTree()
	: _root(NULL) {}
	AvlTree(const AvlTree& from)
	: _root(NULL) {}
	~AvlTree()
	{
		clear();
	}

	AvlTree& operator=(const AvlTree& rhs)
	{
		return *this;
	}

	bool insert(const T& key)
	{
		if (!_root)
			_root = _M_new_node(key, NULL);
		else if (_M_insert_key(_root, key))
		{
			_M_update_node(_root);
			_M_check_balance(_root);
		}
		else
			return false;
		return true;
	}

	void print() const
	{
		_M_print_node(_root);
	}

	void clear()
	{
		_M_destroy_tree(_root);
	}

private:

	bool _M_insert_key(Node* node, const T& key)
	{
		if (node->key == key)
			return false;

		if (_compare(key, node->key))
			return _M_check_leaf(node->left, node, key);
		else
			return _M_check_leaf(node->right, node, key);
	}

	bool _M_check_leaf(Node*& dest, Node* parent, const T& key)
	{
		if (dest == NULL)
		{
			dest = _M_new_node(key, parent);
			return true;
		}
		if (_M_insert_key(dest, key))
		{
			_M_update_node(dest);
			_M_check_balance(dest);
			return true;
		}
		return false;
	}

	void _M_update_node(Node* node)
	{
		_M_update_height(node);
		_M_update_balance(node);
	}

	void _M_update_height(Node* node)
	{
		node->height = \
			ft::max(
				_M_get_height(node->left),
				_M_get_height(node->right)
			) + 1;
	}

	void _M_update_balance(Node* node)
	{
		node->balance = _M_get_balance(node);
	}

	int _M_get_height(Node* node)
	{
		if (node == NULL)
			return -1;
		return node->height;
	}

	int _M_get_balance(Node* node)
	{
		return _M_get_height(node->left) - _M_get_height(node->right);
	}

	Node* _M_new_node(const T& key, Node* parent)
	{
		Node* node = _alloc.allocate(1);
		_alloc.construct(node, Node(key, parent));
		return node;
	}

	void _M_destroy_tree(Node* node)
	{
		if (node == NULL)
			return;
		_M_destroy_tree(node->left);
		_M_destroy_tree(node->right);
		delete node;
	}

/* ROTATIONS, PRESERVING AVL PROPERTY */

	void _M_check_balance(Node* node)
	{
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

	void _M_rotate_right(Node* x)
	{
		Node* y = x->left;
		x->left = y->right;
		y->right = x;
		_M_rotate_update_nodes(x, y);
	}

	void _M_rotate_left(Node* x)
	{
		Node* y = x->right;
		x->right = y->left;
		y->left = x;
		_M_rotate_update_nodes(x, y);
	}

	void _M_rotate_update_nodes(Node* x, Node* y)
	{
		_M_rotate_update_parent(x, y);
		_M_update_node(x);
		_M_update_node(y);
	}

	void _M_rotate_update_parent(Node* node, Node* replacement)
	{
		Node* parent = node->parent;
		replacement->parent = parent;
		if (parent == NULL)
			_root = replacement;
		else if (parent->left == node)
			parent->left = replacement;
		else
			parent->right = replacement;
	}


/* UTIL FUNCTIONS */

	void _M_print_node(Node* node) const
	{
		if (node == NULL)
			return;
		std::cout	<< "KEY(" << std::setw(2) << node->key
					<< "), HEIGHT(" << (node)->height
					<< "), BALANCE(" << (node)->balance
					<< ")" << std::endl;
		_M_print_node(node->left);
		_M_print_node(node->right);
	}

};

}


#endif /* AVL_TREE_HPP */
