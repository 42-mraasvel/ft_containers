#ifndef BST_HPP
# define BST_HPP

# include <memory>
# include "less.hpp"
# include "utils.hpp"

# include <iostream>
# include <iomanip>

namespace ft
{

template <typename T, typename Compare = ft::less<T> >
class BSTree
{
public:

	static const bool RED = true;
	static const bool BLACK = !RED;

/* Member Types */
	typedef T value_type;
	typedef Compare compare_type;

private:
/* Member Variables */
	struct Node
	{
		Node()
		: value(), parent(NULL), left(NULL), right(NULL), height(0), balance(0) {}
		Node(const T& value)
		: value(value), parent(NULL), left(NULL), right(NULL), height(0), balance(0) {}
		~Node() {}

		T value;
		Node* parent;
		Node* left;
		Node* right;
		int height;
		int balance;
	private:
		Node(const Node& from) {}
	};

	Node* _root;
	std::allocator<Node> _alloc;
	compare_type compare;

public:

/* Constructors/Destructors */
	BSTree()
	: _root(NULL) {}

	BSTree(const BSTree& from)
	: _root(NULL)
	{
		*this = from;
	}

	~BSTree()
	{
		_M_clear(_root);
	}

	BSTree& operator=(const BSTree& rhs)
	{
		if (this == &rhs)
			return *this;
		return *this;
	}

/* Member Functions */
	/*
		True if insertion is successful
		False if value already exists
	*/
	bool insert(const T& value)
	{
		if (_root == NULL)
		{
			_root = newNode(value, NULL);
			return true;
		}
		return _M_insert(_root, value);
	}


	void print() const
	{
		printNode(_root);
	}


private:

	bool _M_insert(Node* node, const T& value)
	{
		if (node->value == value)
			return false;
		if (compare(value, node->value))
			return _M_createLeaf(&node->left, value, node);
		else
			return _M_createLeaf(&node->right, value, node);
	}

	bool _M_createLeaf(Node** leaf, const T& value, Node* parent)
	{
		if (*leaf != NULL)
			return  _M_insert(*leaf, value);
		*leaf = newNode(value, parent);
		_M_updateHeightBalance(parent);
		return true;
	}

	void _M_updateHeightBalance(Node* node)
	{
		if (node == NULL)
			return;
		node->height =	ft::max(
							calculateHeight(node->left),
							calculateHeight(node->right)
						) + 1;
		node->balance = calculateBalance(node);
		_M_updateHeightBalance(node->parent);
	}

	Node* newNode(const T& value, Node* parent)
	{
		Node* node = _alloc.allocate(1);
		_alloc.construct(node, value);
		node->height = calculateHeight(node);
		node->balance = calculateBalance(node);
		node->parent = parent;
		return node;
	}

	void _M_clear(Node* node)
	{
		if (node == NULL)
			return;
		_M_clear(node->left);
		_M_clear(node->right);
		_alloc.destroy(node);
		_alloc.deallocate(node, 1);
		_root = NULL;
	}

	int calculateHeight(Node* node) const
	{
		if (node == NULL)
			return -1;
		return node->height;
	}

	int calculateBalance(Node* node) const
	{
		return (calculateHeight(node->left) - calculateHeight(node->right));
	}

	void printNode(Node* node) const
	{
		if (node == NULL)
			return;
		std::cout	<< "VALUE(" << std::setw(2) << node->value
					<< "), HEIGHT(" << (node)->height
					<< "), BALANCE(" << (node)->balance
					<< ")" << std::endl;
		printNode(node->left);
		printNode(node->right);
	}

};

}

#endif /* BST_HPP */
