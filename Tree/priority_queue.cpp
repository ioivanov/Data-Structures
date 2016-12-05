#include "bintree.cpp"

//приоритетна опашка реализирана като дроично дърво
template <typename T>
class PriorityQueue : BinaryTree<T> {
private:
	using P = BinaryTreePosition<T>;

	//вмъкваме елемент на някое празно място
	//след което наместваме елементите
	void insertAndSiftUp(P pos, T const& x) {
		if (pos) {
			//избираме почти на случаен принцип
			//към кое поддърво да продължим
			P newpos = (x % 2) ? -pos : +pos;
			//рекурсивно извикване за избраното дърво
			insertAndSiftUp(newpos, x);
			//премества елемент с по-висок приоритет нагоре
			if (*newpos > *pos)
				swap(*newpos, *pos);
		}
		else {
			//вмъкването се случва когато намерим празна позиция
			//т.е. можем спокойно да запишем на нейно място
			BinaryTree<T>::assignFrom(pos, BinaryTree<T>(x));
		}
	}

	//намира листо на дадето като позиция поддърво
	P findLeaf(P pos) const {
		//ако няма наследници връщаме позицията
		if (!pos || (!- pos && !+ pos))
			return pos;
		//ако няма ляв търсим десен
		if (!- pos)
			return findLeaf(+pos);
		if (!+ pos)
			return findLeaf(-pos);
		return findLeaf((*pos % 2) ? -pos : +pos);
	}

	//връща по-голямото дете
	P maxChild(P pos) {
		if (!- pos)
			return +pos;
		if (!+ pos)
			return -pos;
		return *-pos > *+pos ? -pos : +pos;

	}

	//сменя корена с най-голямото дете
	//така елемента в корена ще слиза
	//докато не намери позицията си
	void siftDown(P pos) {
		if (pos) {
			P maxcpos = maxChild(pos);
			if (maxcpos && *pos < *maxcpos)
				swap(*maxcpos, *pos);
			siftDown(maxcpos);
		}
	}

public:
	//O(1)
	bool empty() const { return BinaryTree<T>::empty(); }

	//O(1)
	T head() { return *BinaryTree<T>::root(); }

	//O(n)
	void enqueue_prioritized(T const& x) {
		insertAndSiftUp(BinaryTree<T>::root(), x);
	}

	//O(1)
	T dequeue_highest() {
		P rpos = BinaryTree<T>::root();
		T result = head();
		P pos = findLeaf(rpos);
		swap(*pos, *rpos);
		BinaryTree<T>::deleteAt(pos);
		siftDown(rpos);
		return result;
	}

};
