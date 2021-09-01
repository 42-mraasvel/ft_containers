#ifndef AVL_TREE_HPP
# define AVL_TREE_HPP

#include "less.hpp"
#include "utils.hpp"
#include "avl_iterator.hpp"

#include <iostream>
#include <iomanip>

namespace ft
{

template <typename T, typename Compare = ft::less<T> >
class AvlTree
{
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

		/*
		  Return min in right subtree
		  If no right subtree: go up the tree
		*/
		Node* next() const
		{

			Node* current = _M_find_min(this->right);

			if (current == NULL)
			{
				const Node* prev = this;
				current = this->parent;
				while (current)
				{
					if (prev == current->left)
						break;
					prev = current;
					current = current->parent;
				}
			}
			return current;
		}

		T key;
		Node* left;
		Node* right;
		Node* parent;
		int balance;
		int height;
	};

public:
	typedef T value_type;
	typedef Compare compare_type;
	typedef size_t size_type;
	typedef TreeIterator<Node, T> iterator;

	Node* _root;
	Node* _min;
	compare_type _compare;
	std::allocator<Node> _alloc;
	size_type _size;

public:

	AvlTree()
	: _root(NULL), _min(NULL), _size(0) {}
	AvlTree(const AvlTree& from)
	: _root(NULL), _min(NULL), _size(0) {}
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
		if (_min == NULL || _compare(key, _min->key))
			_min = _M_find_min(root());
		_size += 1;
		return true;
	}

	size_type erase(const T& key)
	{
		size_type old_size = _size;

		_M_delete_node(_M_find(key, _root));

		return old_size == _size ? 0 : 1;
	}

	void print() const
	{
		_M_print_node(_root);
	}

	void clear()
	{
		_M_destroy_tree(_root);
	}

	size_type size() const
	{
		return _size;
	}

	Node* root()
	{
		return _root;
	}

/* Iterator */

	iterator begin()
	{
		return iterator(_min);
	}

	iterator end()
	{
		return iterator(NULL);
	}

public:

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

	void _M_destroy_node(Node* node)
	{
		_alloc.destroy(node);
		_alloc.deallocate(node, 1);
	}

	void _M_destroy_tree(Node* node)
	{
		if (node == NULL)
			return;
		_M_destroy_tree(node->left);
		_M_destroy_tree(node->right);
		delete node;
	}

	Node* _M_find(const T& key, Node* node)
	{
		if (node == NULL || node->key == key)
			return node;
		if (_compare(key, node->key))
			return _M_find(key, node->left);
		else
			return _M_find(key, node->right);
	}

	Node* _M_find_max(Node* node)
	{
		if (node == NULL)
			return NULL;
		while (node->right != NULL)
			node = node->right;
		return node;
	}

	static Node* _M_find_min(Node* node)
	{
		if (node == NULL)
			return NULL;
		while (node->left != NULL)
			node = node->left;
		return node;
	}

	void _M_delete_node(Node* node)
	{

		if (node == NULL)
			return;


		int num_children = _M_count_children(node);
		Node* parent = node->parent;
		if (num_children == 2)
		{
			_M_swap_node(node, _M_find_max(node->left));
			_M_delete_node(node);
			return;
		}
		else if (num_children == 0)
		{
			_M_replace_parent(node, NULL);
			_M_destroy_node(node);
		}
		else if (node->right != NULL)
		{
			_M_replace_parent(node, node->right);
			_M_destroy_node(node);
		}
		else if (node->left != NULL)
		{
			_M_replace_parent(node, node->left);
			_M_destroy_node(node);
		}
		_M_update_parents(parent);
	}


	void _M_update_parents(Node* node)
	{
		while (node != NULL)
		{
			/* Can this be problematic in terms of check_balance modifying the position of node? */
			_M_update_node(node);
			_M_check_balance(node);
			node = node->parent;
		}
	}

	int _M_count_children(Node* node)
	{
		return static_cast<int> (node->left != NULL) + static_cast<int> (node->right != NULL);
	}

/* SWAP NODES */

	void _M_swap_node(Node* x, Node* y)
	{
		if (x->parent == y)
			_M_swap_node(y, x);
		ft::swap(x->parent, y->parent);
		ft::swap(x->left, y->left);
		ft::swap(x->right, y->right);
		if (x->parent == x)
			_M_swap_adjust(x, y);
		_M_swap_update_parent_children(x, y);
	}

	void _M_swap_adjust(Node* x, Node* y)
	{
		if (y->left == y)
			y->left = x;
		else if (y->right == y)
			y->right = x;
		x->parent = y;
	}

	void _M_swap_update_parent_children(Node* x, Node* y)
	{
		_M_update_parent(x, y);
		_M_update_parent(y, x);
		_M_child_update_parent(x);
		_M_child_update_parent(y);
	}

	void _M_child_update_parent(Node* x)
	{
		if (x->left)
			x->left->parent = x;
		if (x->right)
			x->right->parent = x;
	}

	void _M_update_parent(Node* x, Node* y)
	{
		if (x->parent == NULL)
			_root = x;
		else if (x->parent != y)
		{
			if (x->parent->left == y)
				x->parent->left = x;
			else if (x->parent->right == y)
				x->parent->right = x;
		}
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
		if (x->left)
			x->left->parent = x;
		y->right = x;
		_M_rotate_update_nodes(x, y);
		x->parent = y;
	}

	void _M_rotate_left(Node* x)
	{
		Node* y = x->right;
		x->right = y->left;
		if (x->right)
			x->right->parent = x;
		y->left = x;
		_M_rotate_update_nodes(x, y);
		x->parent = y;
	}

	void _M_rotate_update_nodes(Node* x, Node* y)
	{
		_M_replace_parent(x, y);
		_M_update_node(x);
		_M_update_node(y);
	}

	void _M_replace_parent(Node* node, Node* replacement)
	{
		if (replacement != NULL)
			replacement->parent = node->parent;
		_M_parent_update_child(node, replacement);
	}

	void _M_parent_update_child(Node* node, Node* replacement)
	{
		Node* parent = node->parent;
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
