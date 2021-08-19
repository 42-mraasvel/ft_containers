#include "avl_tree.hpp"
#include "bst.hpp"
#include <iostream>

int TestAVL()
{
	ft::BSTree<int> tree;

	std::cout << std::boolalpha;

	tree.insert(10);
	tree.insert(7);
	tree.insert(6);
	tree.insert(8);
	tree.insert(9);
	tree.insert(1);
	tree.insert(11);
	tree.insert(20);
	tree.insert(14);
	tree.insert(22);

	tree.print();

	std::cout << ft::BSTree<int>::RED << std::endl;

	return 0;
}
