#include "stdafx.h"
#include <list>
#include <queue>
#include <iostream>
#include "tree.cpp"

using std::cout;
using std::queue;
using std::list;

bool isLeaf(const Tree& tree) {
	return tree.getSubtrees().empty();
}

void DFS(const Tree& tree) {
	// обработваме корена
	cout << tree.getRoot() << ' ';

	// извикваме рекурсивно DFS за всяко от поддърветата
	for (list<Tree>::const_iterator it = tree.getSubtrees().begin(); it != tree.getSubtrees().end(); ++it) {
		DFS(*it);
	}
}

void BFS(Tree const& tree)
{
	//по-доброто решение е с опашка от върхове, като използваме функция за намиране на наследниците на даден връх
	//така ще пестим и време и памет
	queue<Tree> q;

	//list<int> path съхранява пътя ако е необходимо
	//size_t level=1; съхранява индекса на текущото ниво

	q.push(tree);

	while (!q.empty())
	{
		Tree const& t = q.front();
		//обработваме корена, намиращ се в началото на опашката
		cout << t.getRoot();

		//слагаме всичките наследници на корена в опашката
		for (list<Tree>::const_iterator it = t.getSubtrees().begin(); it != t.getSubtrees().end(); it++)
		{
			q.push(*it);
		}

		//махаме корена - dequeue
		q.pop();
	}
}


int main() {
	// (1 (2 (3) (4)) (5 (6) (7) (8)) (9))
	Tree tree(1);
	tree.addChild(Tree(2).addChild(Tree(3)).addChild(Tree(4)))
		.addChild(Tree(5).addChild(Tree(6)).addChild(Tree(7)).addChild(Tree(8)))
		.addChild(Tree(9));
	cout << tree;
	return 0;
}
