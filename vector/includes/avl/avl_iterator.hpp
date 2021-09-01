#ifndef AVL_ITERATOR_HPP
# define AVL_ITERATOR_HPP

namespace ft
{

template <typename T, typename V>
class TreeIterator
{
public:
	typedef T node_type;
	typedef V value_type;

	TreeIterator()
	: node(NULL) {}

	TreeIterator(const TreeIterator& from)
	: node(from.node) {}

	TreeIterator(node_type* node)
	: node(node) {}

	~TreeIterator() {}

	TreeIterator& operator++()
	{
		node = node->next();
		return *this;
	}

	value_type& operator*()
	{
		return node->key;
	}

	bool operator==(const TreeIterator& rhs)
	{
		return node == rhs.node;
	}

	bool operator!=(const TreeIterator& rhs)
	{
		return !(*this == rhs);
	}

private:
	node_type* node;

};

}

#endif /* AVL_ITERATOR_HPP */
