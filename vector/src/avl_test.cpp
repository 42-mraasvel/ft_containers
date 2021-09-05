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
int calculateHeight(ft::NodeAVL<T>* node)
{
	if (node == NULL)
		return -1;
	
	return ft::max(calculateHeight(node->left()), calculateHeight(node->right())) + 1;
}

template <typename T>
int calculateBalance(ft::NodeAVL<T>* node)
{
	return calculateHeight(node->left()) - calculateHeight(node->right());
}

template <typename T>
bool validNode(ft::NodeAVL<T>* node)
{
	int balance = calculateBalance(node);

	assert(node->get_height() == calculateHeight(node));
	assert(node->get_balance() == balance);
	assert(ft::abs(calculateBalance(node)) <= 1);

	if (node->left())
	{
		assert(node->left()->parent() == node);
		assert(node->left()->key().first < node->key().second);
	}
	
	if (node->right())
	{
		assert(node->right()->parent() == node);
		assert(node->right()->key().first > node->key().second);
	}

	return true;
}

template <typename T>
bool validAvl(ft::NodeAVL<T>* root)
{
	if (root == NULL)
		return true;

	if (!validAvl(root->left()))
		return false;
	if (!validNode(root))
		return false;
	if (!validAvl(root->right()))
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

typedef ft::NodeAVL < ft::pair<const int, int> > node_type;

int TestAVL()
{
	ft::map<int, int> m;



	/* CONFIRM AVL */
	node_type* ptr = m.root();
	validAvl(ptr);

	return 0;
}
