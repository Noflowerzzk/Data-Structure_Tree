#pragma once
template<typename Object>
class BinarySearchTree
{
public:
	BinarySearchTree()
		:root{ nullptr } { }
	BinarySearchTree(const BinarySearchTree& rhs)
		:root{ nullptr }
	{
		this->root = clone(rhs.root);
	}
	BinarySearchTree(BinarySearchTree&& rhs)
		:root{ nullptr }
	{
		root = clone(rhs.root);
	}
	~BinarySearchTree()
	{
		makeEmpty();
	}

	Object& operator = (const BinarySearchTree& rhs)
	{
		return root = rhs.root;
	}
	Object& operator = (BinarySearchTree&& rhs)
	{
		return root = rhs.root;
	}

	const Object& findMin() const
	{
		findMin(root);
	}
	const Object& findMax() const
	{
		findMax(root);
	}

	bool contains(const Object& x)
	{
		contains(root);
	}
	bool isEmpty() const
	{
		return root == nullptr;
	}

	void printTree(std::ostream& out)
	{
		if (isEmpty())
			out << "Empty Tree!";
		else
			printTree(root, out);
	}
};