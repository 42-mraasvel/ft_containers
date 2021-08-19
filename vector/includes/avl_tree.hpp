#ifndef AVL_TREE_HPP
# define AVL_TREE_HPP

namespace ft
{

template <typename T>
class AvlTree
{
private:

	struct Node
	{
		T value;
		Node* left;
		Node* right;
	};

	Node* root;

public:

};

}


#endif /* AVL_TREE_HPP */
