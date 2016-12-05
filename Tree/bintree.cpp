#include <iostream>
using namespace std;

//подобно на свързан списък имаме структура възел
template <typename T>
struct TreeNode {
	//съдържаща данни
	T data;
	//указател към ляв и десен възел
	TreeNode *left, *right;

	TreeNode(T const& _data = T(),
		TreeNode* _left = NULL,
		TreeNode* _right = NULL)
		: data(_data), left(_left), right(_right) {}
};

//тази декларация ни позволява да използваме двоичното 
//дърво преди да сме го реализирали
template <typename T>
class BinaryTree;

//реализираме позиция в дърво като двоен указател
//това помага за много бързо разместване на поддървета
template <typename T>
class BinaryTreePosition {
private:
	//представлява указател към указател към дърво
	TreeNode<T>** p;
public:
	BinaryTreePosition(TreeNode<T>*& rp) : p(&rp) {}

	//този оператор позволява конвертирането на
	//позиция към истина или лъжа
	operator bool() const {
		return *p != NULL;
	}

	//позволява поставянето на отрицание пред позиция
	bool operator!() const {
		return *p == NULL;
	}

	//връща стойността на корена
	T& operator*() const {
		return (*p)->data;
	}

	//прави преместване на дясно ако е възможно
	BinaryTreePosition operator+() const {
		if (*p == NULL)
			return *this;
		return BinaryTreePosition((*p)->right);
	}

	//преместване на ляво ако е възможно
	BinaryTreePosition operator-() const {
		if (*p == NULL)
			return *this;
		return BinaryTreePosition((*p)->left);
	}

	//позволява достъп на BinaryTree<T> до методите на текущия клас
	friend class BinaryTree<T>;

};

//двоичното дърво реализираме подобно на свързан списък
template <typename T>
class BinaryTree {
private:
	//указател към корена на дървото
	TreeNode<T>* r;
	
	//интересно тук е извеждането на съобщението
	//това ще ни покаже колко пъти се копира структурата
	TreeNode<T>* copyNode(TreeNode<T>* n) {
		if (n == NULL)
			return n;
		cout << "Copying tree" << endl;
		return new TreeNode<T>(n->data, copyNode(n->left),
			copyNode(n->right));
	}

	//тъй като всеки възел е заделен с new
	//трябва първо да изтрием наследниците
	//и след това текущият възел
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
		// като я "открадваме", т.е. в дървото, от което вземаме
		// нулираме указателя
		from = NULL;
		// изтриваме старата стойност, за да предотвратим изтичане
		// на памет
		eraseNode(toDelete);
	}


public:

	using P = BinaryTreePosition<T>;

protected:
	//
	void assignFrom(P to, P from) {
		assignFrom(*to.p, *from.p);
	}

public:
	BinaryTree() : r(NULL) {}
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


	BinaryTree leftTree() const {
		return BinaryTree(r->left);
	}

	BinaryTree rightTree() const {
		return BinaryTree(r->right);
	}

	bool empty() const {
		return r == NULL;
	}

};


template <typename T>
ostream& operator<<(ostream& os, BinaryTree<T> const& bt) {
	if (bt.empty())
		return os << '.';
	return os << '(' << *bt.root() << ' ' << bt.leftTree()
		<< ' ' << bt.rightTree() << ')';
}


template <typename T>
ostream& operator<<(ostream& os, BinaryTreePosition<T> pos) {
	if (!pos)
		return os << '.';
	return os << '(' << *pos << ' ' << -pos
		<< ' ' << +pos << ')';
}
