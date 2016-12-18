#include "bintree.cpp"

template <typename T>
class BinarySearchTree : protected BinaryTree<T> {
public:
	using typename BinaryTree<T>::P;

private:

  //метод за намиране на позицията на връх
	P findPosition(T const& x) {
		P pos = BinaryTree<T>::root();
    //търсим докато пизицията е валидна и не сме намерили елемента
		while (pos && *pos != x)
    //ако търсеният елемент е по-малък от корена отиваме наляво
			if (x < *pos)
				pos = -pos;
      //ако е по-голям отиваме надясно
			else
				pos = +pos;
		// *pos == x -- намерихме!
		// !pos --- няма го
		return pos;
	}

public:

	T* search(T const& x) {
		P pos = findPosition(x);
		if (pos)
			return &*pos;
		return NULL;
	}
  
  //метод за вмъкване на елемент
	bool insert(T const& x) {
    //намираме на коя позиция трябва да се вмъкне
		P pos = findPosition(x);
    //ако позицията е празна тогава записваме новата стойност
		if (!pos) {
			BinaryTree<T>::assignFrom(pos, x);
			return true;
		}
		return false;
	}

  //метод за премахване на елемент
	bool remove(T const& x) {
    //искаме да премахнем съществуващ елемент от дървото
		P pos = findPosition(x);
    //неговата позиция трябва да е валидна
		if (!pos)
			return false;
		if (+pos && -pos) {
			// има и двете поддървета
			// трябва да заменим корена с M
			// където M е най-малкият (най-левият) елемент
			// в дясното поддърво
			P m = +pos;
			// вървим наляво докато можем
			while (-m) m = -m;
			// Като не можем повече (!-m), тогава сме на най-малкия елемент

			// числото в m отива на мястото на корена
			*pos = *m;
			// сведохме задачата до случая, когато нямаме ляво поддърво
			pos = m;
		}
		// тук сме сигурни, че !-pos || !+pos
		if (!-pos)
			// закачаме дясното дете на мястото на родителя
			BinaryTree<T>::assignFrom(pos, +pos);
		else
			// !+pos
			// закачаме лявото дете на мястото на родителя
			BinaryTree<T>::assignFrom(pos, -pos);

		return true;
	}
};
