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

	BinarySearchTree& operator = (const BinarySearchTree& rhs)
	{
		root = rhs.root;
		return *this;
	}
	BinarySearchTree& operator = (BinarySearchTree&& rhs)
	{
		root = rhs.root;
		return *this;
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
		contains(x, root);
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
			printTree(root, cout);
	}
	void makeEmpty()
	{
		makeEmpty(root);
	}
	void insert(const Object& x)
	{
		insert_private(x);
	}
	void insert(Object&& x)
	{
		insert_private(x);
	}
	void remove(const Object& x)
	{
		remove(x, root);
	}
private:
	struct BinaryNode
	{		
		Object element;
		BinaryNode* left;
		BinaryNode* right;

		BinaryNode(const Object& ele, BinaryNode* l, BinaryNode* r)
			:element{ ele }, left{ l }, right{ r } { }
		BinaryNode(Object&& ele, BinaryNode* l, BinaryNode* r)
			:element{ std::move(ele) }, left{ l }, right{ r } { }
	};

	BinaryNode* root;

	void insert_private(const Object& x)
	{
		BinaryNode* t = root;
		// bool side = true;

		while (t != nullptr)
		{
			if (x < t->element)
			{
				if (t->left == nullptr)
				{
					t->left = new BinaryNode{ x, nullptr, nullptr };
					return;
				}
				else
				{
					t = t->left;
					continue;
				}
			}
			else if (x > t->element)
			{
				if (t->right == nullptr)
				{
					t->right = new BinaryNode{ x, nullptr, nullptr };
					return;
				}
				else
				{
					t = t->right;
					continue;
				}
			}
			else
				return;
		}

		root = new BinaryNode{ x, nullptr, nullptr };
		return;
	}
	void insert_private(Object&& x, BinaryNode*& t)
	{
		{
			BinaryNode* t = root;
			// bool side = true;

			while (t != nullptr)
			{
				if (std::move(x) < t->element)
				{
					if (t->left == nullptr)
					{
						t->left = new BinaryNode{ std::move(x), nullptr, nullptr };
						return;
					}
					else
					{
						t = t->left;
						continue;
					}
				}
				else if (std::move(x) > t->element)
				{
					if (t->right == nullptr)
					{
						t->right = new BinaryNode{ std::move(x), nullptr, nullptr };
						return;
					}
					else
					{
						t = t->right;
						continue;
					}
				}
				else
					return;
			}

			root = new BinaryNode{ std::move(x), nullptr, nullptr };
			return;
		}
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
			remove(t->element, t->right);  // ���Ľ�
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
	void printTree(BinaryNode* t, ostream& out) const
	{
		if (t != nullptr)
		{
			printTree(t->left, out);
			cout << t->element << endl;
			printTree(t->right, out);
		}
	}
	BinaryNode* clone(BinaryNode* t) const
	{
		if (t == nullptr)
			return nullptr;
		else
			return new BinaryNode{ t->element, clone(t->left), clone(t->right) };
	}
};

void BinarySearchTree_Runner()
{
	BinarySearchTree<int> t;

	for (int i = 0; i < 20; i++)
	{
		t.insert(i + 1);
	}

	t.printTree(cout);

	BinarySearchTree<int> t1{ t };
	t1.printTree(cout);

	BinarySearchTree<int> t2 = t;
	t2.printTree(cout);

	cout << endl;

	t.insert(21);
	t.printTree(cout);

	t.insert(11);
	t.printTree(cout);

	t.insert(-2);
	t.printTree(cout);
}