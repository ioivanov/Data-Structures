#include "stdafx.h"
#include <list>
#include <iostream>
using std::list;
using std::ostream;

class Tree {
private:
	int root;
	// списък от децата (наследниците на корена)
	list<Tree> subtrees;

public:
	// при конструирането на дърво задаваме само корена
	// за добавяне на деца използваме addChild
	Tree(int _root = 0) : root(_root) {}

	// добавя поддърво child към списъка с поддърветата subtrees
	// връща референция към дървото,
	// за да можем да викаме addChild няколко пъти за дървотo, т.е така:
	// tree.addChild(1).addChild(2).addChild(3);
	Tree& addChild(Tree const& child)
	{
		subtrees.push_back(child);
		return *this;
	}

	// връща стойността на корена
	int getRoot() const { return root; }

	// връща референция към списъка от поддървета
	list<Tree> const& getSubtrees() const { return subtrees; }

	// извежда дървото
	friend ostream& operator<<(ostream& os, Tree const& tree)
	{
		os <<'('<< tree.getRoot();
		for (list<Tree>::const_iterator it = tree.getSubtrees().begin(); it != tree.getSubtrees().end(); it++)
		{
			os <<' '<< *it;
		}
		return os << ')';
	}
};
