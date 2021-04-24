#pragma once
template<typename Object>
class AvlTree
{
public:
	AvlTree()
		:root{ nullptr } { }
	AvlTree(const AvlTree& rhs)
		:root{ nullptr }
	{
		this->root = clone(rhs.root);
	}
	AvlTree(AvlTree&& rhs)
		:root{ nullptr }
	{
		root = clone(rhs.root);
	}
	~AvlTree()
	{
		makeEmpty();
	}

	AvlTree& operator = (const AvlTree& rhs)
	{
		root = rhs.root;
		return *this;
	}
	AvlTree& operator = (AvlTree&& rhs)
	{
		root = rhs.root;
		return *this;
	}

	const Object& findMin() const
	{
		return findMin(root)->element;
	}
	const Object& findMax() const
	{
		return findMax(root)->element;
	}

	bool contains(const Object& x)
	{
		return contains(x, root);
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
	struct AvlNode
	{
		Object element;
		AvlNode* left;
		AvlNode* right;
		int height;

		AvlNode(const Object& ele, AvlNode* l, AvlNode* r, int h = 0)
			:element{ ele }, left{ l }, right{ r }, height{ h } { };
		AvlNode(Object&& ele, AvlNode* l, AvlNode* r, int h = 0)
			:element{ std::move(ele) }, left{ l }, right{ r }, height{ h } { }
	};

	AvlNode* root;
	static const int ALLOWED_BALANCE = 1;

	void insert_private(const Object& x)
	{
		AvlNode* t = root;
		// bool side = true;

		while (t != nullptr)
		{
			if (x < t->element)
			{
				if (t->left == nullptr)
				{
					t->left = new AvlNode{ x, nullptr, nullptr };
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
					t->right = new AvlNode{ x, nullptr, nullptr };
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

		root = new AvlNode{ x, nullptr, nullptr };
		return;
	}
	void insert_private(Object&& x, AvlNode*& t)
	{
		{
			AvlNode* t = root;
			// bool side = true;

			while (t != nullptr)
			{
				if (std::move(x) < t->element)
				{
					if (t->left == nullptr)
					{
						t->left = new AvlNode{ std::move(x), nullptr, nullptr };
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
						t->right = new AvlNode{ std::move(x), nullptr, nullptr };
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

			root = new AvlNode{ std::move(x), nullptr, nullptr };
			return;
		}
	}
	void remove(const Object& x, AvlNode*& t)  /**/
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
			AvlNode* Old = t;
			t = (t->left != nullptr) ? t->left : t->right;
			delete Old;
		}
	}
	AvlNode* findMin(AvlNode* t) const
	{
		if (t != nullptr)
			while (t->left != nullptr)
				t = t->left;
		return t;
	}
	AvlNode* findMax(AvlNode* t) const
	{
		if (t != nullptr)
			while (t->right != nullptr)
				t = t->right;
		return t;
	}
	bool contains(const Object& x, AvlNode* t) const
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
	void makeEmpty(AvlNode*& t)
	{
		if (t != nullptr)
		{
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		t = nullptr;
	}
	void printTree(AvlNode* t, ostream& out) const
	{
		if (t != nullptr)
		{
			printTree(t->left, out);
			cout << t->element << endl;
			printTree(t->right, out);
		}
	}
	AvlNode* clone(AvlNode* t) const
	{
		if (t == nullptr)
			return nullptr;
		else
			return new AvlNode{ t->element, clone(t->left), clone(t->right) };
	}

	inline int height(AvlNode* t)
	{
		return t == nullptr ? -1 : t->height;
	}
};

