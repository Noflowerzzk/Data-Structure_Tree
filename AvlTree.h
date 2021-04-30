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
			if (x == t->element || x == t->left->element || x == t->right->element )
				return;
			else if (x < t->left->element) //向X
			{
				if (t->left->left == nullptr) //插入
				{
					t->left->left = new AvlNode{ x,nullptr,nullptr };
					if (t->left->right == nullptr)
						rotateWithLeftChild(t);
					return;
				}
				else if (height(t->left) + 1 - height(t->right) > ALLOWED_BALANCE) //k2左深
				{
					rotateWithLeftChild(t);
					t = t->left; //x
					continue;
				}
				else
				{
					t = t->left->left;
					continue;
				}
			}
			else if (x > t->right->element) //向X
			{
				if (t->right->right == nullptr) //插入
				{
					t->right->right = new AvlNode{ x,nullptr,nullptr };
					if (t->right->left == nullptr)
						rotateWithRightChild(t);
					return;
				}
				else if (height(t->right) + 1 - height(t->left) > ALLOWED_BALANCE) //k2左深
				{
					rotateWithRightChild(t);
					t = t->right; //x
					continue;
				}
				else
				{
					t = t->right->right;
					continue;
				}
			}
			else if (x<t->element && x>t->left->element) //双旋转,向下图k2
			{
				if (x < t->left->right->element) //向B
				{
					if (t->left->right->left == nullptr)
					{
						t->left->right->left = new AvlNode{ x,nullptr,nullptr };
						if (t->left->right->right == nullptr)
							doubleWithLeftChild(t);
						return;
					}
					else if (height(t->left->right) + 1 - height(t->left) > ALLOWED_BALANCE) //左双
					{
						doubleWithLeftChild(t);
						t = t->left->right;
						continue;
					}
					else
					{
						t = t->left->right->left;
						continue;
					}
				}
				else if (x > t->left->right->element) //向C
				{
					if (t->left->right->right == nullptr) //
					{
						t->left->right->right = new AvlNode{ x,nullptr,nullptr };
						if (t->left->right->left == nullptr)
							doubleWithLeftChild(t);
						return;
					}
					else if (height(t->left->right) + 1 - height(t->left) > ALLOWED_BALANCE) //左双
					{
						doubleWithLeftChild(t);
						t = t->right->left;
						continue;
					}
					else
					{
						t = t->left->right->right;
						continue;
					}
				}
			}
			else if (x>t->element && x<t->right->element) //双旋转,向下图k2
			{
				if (x > t->right->left->element) //向B
				{
					if (t->right->left->right == nullptr)
					{
						t->right->left->right = new AvlNode{ x,nullptr,nullptr };
						if (t->right->left->left == nullptr)
							doubleWithRightChild(t);
						return;
					}
					else if (height(t->right->left) + 1 - height(t->right) > ALLOWED_BALANCE) //左双
					{
						doubleWithRightChild(t);
						t = t->right->left;
						continue;
					}
					else
					{
						t = t->right->left->right;
						continue;
					}
				}
				else if (x < t->right->left->element) //向C
				{
					if (t->right->left->left == nullptr) //
					{
						t->right->left->left = new AvlNode{ x,nullptr,nullptr };
						if (t->right->left->right == nullptr)
							doubleWithRightChild(t);
						return;
					}
					else if (height(t->right->left) + 1 - height(t->right) > ALLOWED_BALANCE) //左双
					{
						doubleWithRightChild(t);
						t = t->left->right;
						continue;
					}
					else
					{
						t = t->right->left->left;
						continue;
					}
				}
			}
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
			for (int i = t->height; i > 0; i++)
				cout << '\t';
			printTree(t->left, out);
			for (int i = t->height; i >= 0; i++)
				cout << '\t';
			cout << t->element << endl;
			for (int i = t->height; i > 0; i++)
				cout << '\t';
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
	void rotateWithLeftChild(AvlNode*& k2)
	{
		AvlNode* k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;

		k2->height = max(height(k2->left), height(k2->right)) + 1;
		k1->height = max(height(k1->left), k2->height) + 1;
		
		k2 = k1;
	}
	void rotateWithRightChild(AvlNode*& k2)
	{
		AvlNode* k1 = k2->right;
		k2->right = k1->left;
		k1->left = k2;

		k2->height = max(height(k2->right), height(k2->left)) + 1;
		k1->height = max(height(k1->right), k2->height) + 1;

		k2 = k1;
	}
	void doubleWithLeftChild(AvlNode*& k3)
	{
		AvlNode*& k2 = k3->left->right;
		k3->left->right = k2->left;
		k2->left = k3->left;
		k3->left = k2->right;
		k2->right = k3;

		k2->left->height = max(height(k2->left->right), height(k2->left->right)) + 1;
		k3->height = max(height(k3->left), height(k3->right)) + 1;
		k2->height = max(height(k2->left), height(k2->right)) + 1;

		k3 = k2;
	}
	void doubleWithRightChild(AvlNode*& k3)
	{
		AvlNode*& k2 = k3->right->left;
		k3->right->left = k2->right;
		k2->right = k3->right;
		k3->right = k2->left;
		k2->left = k3;

		k2->right->height = max(height(k2->right->right), height(k2->right->right)) + 1;
		k3->height = max(height(k3->left), height(k3->right)) + 1;
		k2->height = max(height(k2->left), height(k2->right)) + 1;

		k3 = k2;
	}

};


void AvlTree_runner()
{
	AvlTree<int> t{};

	for (int i = 1; i < 10; i++)
		t.insert(i);

	t.printTree(cout);
}