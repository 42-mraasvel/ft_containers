#ifndef BST_HPP
# define BST_HPP

# include <memory>
# include "less.hpp"
# include "utils.hpp"

# include <iostream>
# include <iomanip>

template <typename T>
void printValue(const T& val)
{
	std::cout << ' ' << val;
}

namespace ft
{

template <typename T, typename Compare = ft::less<T>>
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
		: value(), left(NULL), right(NULL) {}
		Node(const T& value)
		: value(value), left(NULL), right(NULL) {}
		~Node() {}

		T value;
		Node* left;
		Node* right;
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
			_root = newNode(value);
			return true;
		}
		return _M_insert(_root, value);
	}


	void print() const
	{
		printNode(_root);
		// std::cout << "CONTAINS:";
		// _M_applyPostfix(_root, printValue<T>);
		// std::cout << std::endl;
	}


private:
	bool _M_insert(Node* node, const T& value)
	{
		if (node->value == value)
			return false;

		if (compare(value, node->value))
			return _M_createLeaf(&node->left, value);
		else
			return _M_createLeaf(&node->right, value);

	}

	bool _M_createLeaf(Node** leaf, const T& value)
	{
		if (*leaf != NULL)
			return  _M_insert(*leaf, value);
		*leaf = newNode(value);
		return true;
	}

	Node* newNode(const T& value)
	{
		Node* node = _alloc.allocate(1);
		_alloc.construct(node, value);
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

	void _M_applyPrefix(Node* node, void (*f)(const T& value)) const
	{
		if (node == NULL)
			return;
		f(node->value);
		_M_applyPrefix(node->left, f);
		_M_applyPrefix(node->right, f);
	}

	void _M_applyInfix(Node* node, void (*f)(const T& value)) const
	{
		if (node == NULL)
			return;
		_M_applyInfix(node->left, f);
		f(node->value);
		_M_applyInfix(node->right, f);
	}

	void _M_applyPostfix(Node* node, void (*f)(const T& value)) const
	{
		if (node == NULL)
			return;
		_M_applyPostfix(node->left, f);
		_M_applyPostfix(node->right, f);
		f(node->value);
	}

	int calculateHeight(Node* node) const
	{
		if (node == NULL)
			return -1;
		return ft::max(calculateHeight(node->left),
					calculateHeight(node->right)) + 1;
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
					<< "), HEIGHT(" << calculateHeight(node)
					<< "), BALANCE(" << calculateBalance(node) 
					<< ")" << std::endl;
		printNode(node->left);
		printNode(node->right);
	}

};

}

#endif /* BST_HPP */
