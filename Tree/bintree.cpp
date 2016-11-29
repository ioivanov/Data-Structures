#include "stdafx.h"
#include <iostream>
using namespace std;

template <typename T>
struct TreeNode {
	// стойността в корена
	T data;
	//ляво и дясно поддърво
	TreeNode *left, *right;

	TreeNode(T const& _data = T(),
		TreeNode* _left = NULL,
		TreeNode* _right = NULL)
		: data(_data), left(_left), right(_right) {}
};

template <typename T>
class BinaryTree {
private:
	//дървото ни представлява указател към корена (аналогия със свързан списък)
	TreeNode<T>* r;

	TreeNode<T>* copyNode(TreeNode<T>* n) {
		if (n == NULL)
			return n;
		//cout << "Copying tree" << endl;
		//за да откопираме дърво първо копираме корена после викаме функцията за ляво и дясно поддърво
		return new TreeNode<T>(n->data, copyNode(n->left),
			copyNode(n->right));
	}

	//тъй като всяко дърво е заделено с new първо трием наследниците след това себе си
	void eraseNode(TreeNode<T>* n) {
		if (n != NULL) {
			eraseNode(n->left);
			eraseNode(n->right);
			delete n;
		}
	}

	BinaryTree(TreeNode<T>* p) : r(copyNode(p)) {}

	void assignFrom(TreeNode<T>*& to, TreeNode<T>*& from) {
		// Запомняме си старата стойност, за да я изтрием
		TreeNode<T>* toDelete = to;
		// прехвърляме новата стойност
		to = from;
		// като я "открадваме", т.е. в дървото, от което вземаме		// нулираме указателя
		from = NULL;
		// изтриваме старата стойност, за да предотвратим изтичане
		// на памет
		eraseNode(toDelete);
	}
public:
	BinaryTree() : r(NULL) {}

	//конструктор по корен, ляво и дясно дърво
	//трябва да се подават временни променливи защото използваме assignFrom
	BinaryTree(T const& x, BinaryTree<T>&& lt = BinaryTree<T>(),
		BinaryTree<T>&& rt = BinaryTree<T>()) {
		r = new TreeNode<T>(x);
		assignFrom(r->left, lt.r);
		assignFrom(r->right, rt.r);
	}

	BinaryTree(BinaryTree const& bt) : r(copyNode(bt.r)) {
	}

	BinaryTree& operator=(BinaryTree const& bt) {
		if (this != &bt) {
			eraseNode(r);
			r = copyNode(bt.r);
		}
		return *this;
	}

	~BinaryTree() {
		eraseNode(r);
	}

	T root() const {
		if (r == NULL)
			return T();
		return r->data;
	}

	BinaryTree leftTree() const {
		return BinaryTree(r->left);
	}
	BinaryTree rightTree() const {
		return BinaryTree(r->right);
	}
	bool empty() const {
		return r == NULL;
	}

	friend ostream& operator<<(ostream& os, BinaryTree<T> const& bt) 
	{
		if (bt.empty())
			return os << '.';
		return os << '(' << bt.root()<< ' ' << bt.leftTree()
			<< ' ' << bt.rightTree() << ')';
	}
};

template <typename T>
class BinaryTreePosition {
private:
	//двоен указател за да имаме контрол над наследниците
	TreeNode<T>** p;
public:
	BinaryTreePosition(TreeNode<T>*& rp) : p(&rp) {}

	operator bool() const {
		return *p != NULL;
	}

	bool operator!() const {
		return *p == NULL;
	}

	T& operator*() const {
		return (*p)->data;
	}

	BinaryTreePosition operator+() const {
		if (*p == NULL)
			return *this;
		return BinaryTreePosition((*p)->right);
	}

	BinaryTreePosition operator-() const {
		if (*p == NULL)
			return *this;
		return BinaryTreePosition((*p)->left);
	}

	friend class BinaryTree<T>;
};

/*
void assignFrom(P pos, BinaryTree<T>&& t) {
	assignFrom(pos, t.root());
}

void deleteAt(P pos) {
	TreeNode<T>* tmp = NULL;
	assignFrom(*pos.p, tmp);
}

P root() {
	return P(r);
}
*/
