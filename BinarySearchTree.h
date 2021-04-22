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
	void makeEmpty()
	{
		makeEmpty(root);
	}
	void insert(const Object& x)
	{
		insert(x, root);
	}
	void insert(Object&& x)
	{
		insert(x, root);
	}
	void remove(const Object& x)
	{
		remove(x, root);
	}
private:
	struct BinaryNode
	{
		BinaryNode* left;
		BinaryNode* right;
		Object element;

		BinaryNode(BinaryNode*& l, BinaryNode*& r, Object& ele)
			:left{ l }, right{ r }, element{ ele } { }
		BinaryNode(BinaryNode* l, BinaryNode* r, Object ele)
			:left{ l }, right{ r }, element{ ele } { }
	};
	void insert(const Object& x, BinaryNode*& t)
	{
		if (t == nullptr)
			t = new BinaryNode{ x, nullptr, nullptr };
		else if (x < t->element)
			insert(x, t->left);
		else if (x > t->element)
			insert(x, t->right);
		else
			;  // 重复元
	}
	void insert(Object&& x, BinaryNode*& t)
	{
		if (t == nullptr)
			t = new BinaryNode{ std::move(x), nullptr, nullptr };
		else if (x < t->element)
			insert(std::move(x), t->left);
		else if (x > t->element)
			insert(std::move(x), t->right);
		else
			;  // 重复元
	}
	void remove(const Object& x, BinaryNode*& t)  /**/
	{
		if (t == nullptr)
			return;
		else if (x < t->element)
			remove(x, t->left);
		else if (x > t->element)
			remove(x, t->right);
		else if (t->left != nullptr && t->right != nullptr)
		{
			t->element = findMin(t->right)->element;
			remove(t->element, t->right);  // 待改进
		}
		else
		{
			BinaryNode* Old = t;
			t = (t->left != nullptr) ? t->left : t->right;
			delete Old;
		}
	}
	BinaryNode* findMin(BinaryNode* t) const
	{
		if (t == nullptr)
			return nullptr;
		else if (t->left == nullptr)
			return t;
		else
			return findMin(t->left);
	}
	BinaryNode* findMax(BinaryNode* t) const
	{
		if (t == nullptr)
			return nullptr;
		else if (t->right == nullptr)
			return t;
		else
			return findMax(t->right);
	}
	bool contains(const Object& x, BinaryNode* t) const
	{
		if (t == nullptr)
			return false;
		else if (x < t->element)
			return contains(x, t->left);
		else if (x > t->element)
			return contains(x, t->right);
		else
			return true;
	}
	void makeEmpty(BinaryNode*& t)
	{
		if (t != nullptr)
		{
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		t = nullptr;
	}
	void printTree(BinaryNode* t, std::ostream out) const
	{
		if (t == nullptr)
			return;
		else if (t->left != nullptr && t->right != nullptr)
		{
			printTree(t->left, out);
			out << t->element << endl;
			printTree(t->right, out);
		}
		else
			out << t->element << endl;
	}
	BinaryNode* clone(BinaryNode* t) const
	{
		if (t == nullptr)
			return nullptr;
		else
			return new BinarySearchTree{ t->element, clone(t->left), clone(t->right) };
	}
};