#include "avl_tree.hpp"
#include "bst.hpp"
#include "node_avl.hpp"
#include "tree_avl.hpp"
#include "map.hpp"
#include <iostream>
#include <map>
#include <utility>
#include <cassert>


template <typename T>
int calculateHeight(typename ft::AvlTree<T>::Node* node)
{
	if (node == NULL)
		return -1;
	
	return ft::max(calculateHeight<T>(node->left), calculateHeight<T>(node->right)) + 1;
}

template <typename T>
int calculateBalance(typename ft::AvlTree<T>::Node* node)
{
	return calculateHeight<T>(node->left) - calculateHeight<T>(node->right);
}

template <typename T>
bool validNode(typename ft::AvlTree<T>::Node* node)
{
	int balance = calculateBalance<T>(node);
	
	assert(node->height == calculateHeight<T>(node));
	assert(node->balance == balance);
	assert(ft::abs(calculateBalance<T>(node)) <= 1);

	if (node->left)
	{
		assert(node->left->parent == node);
		assert(node->left->key < node->key);
	}
	
	if (node->right)
	{
		assert(node->right->parent == node);
		assert(node->right->key > node->key);
	}

	return true;
}

template <typename T>
bool validAvl(typename ft::AvlTree<T>::Node* root)
{
	if (root == NULL)
		return true;

	if (!validAvl<T>(root->left))
		return false;
	if (!validNode<T>(root))
		return false;
	if (!validAvl<T>(root->right))
		return false;
	return true;
}

/*
Rotation Tests:


	Simple Left-Heavy:
		Right
		Left-Right Rotation
	Insertions:
		41
		20
		65
		50
		11
		29
		26
		23 | 27 (straight vs zig-zag)

	Simple Right-Heavy:
		Left
		Right-Left Rotation
	Insertions:


	Complex Rotation!
	Insertions:
		50
		60
		30
		20
		40
		45

	Insertions:
		0
		1
		...
		n 

*/

typedef ft::AvlTree<int> tree_type;
typedef typename ft::AvlTree<int>::Node node_type;

int TestAVL()
{
	ft::map<int, int> m;

	return 0;
}
