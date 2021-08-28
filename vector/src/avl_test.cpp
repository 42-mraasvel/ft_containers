#include "avl_tree.hpp"
#include "bst.hpp"
#include <iostream>

int TestAVL()
{
	ft::BSTree<int> tree;

	std::cout << std::boolalpha;

	tree.insert(4);
	tree.insert(3);
	tree.insert(1);
	tree.insert(2);
	tree.insert(0);

	tree.print();

	std::cout << ft::BSTree<int>::RED << std::endl;

	return 0;
}
