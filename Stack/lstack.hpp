
#ifndef LSTACK_HPP_
#define LSTACK_HPP_

#include <iostream>
using namespace std;

//Свързаната структура представлява верига от кутийки
//елементите(кутийките) на свързания стек са изградени от:
template <typename T>
struct StackElement {
	T data; //данните, които се съхраняват в стека (пример: числото 256, или символа 'h')
	StackElement* next; // указател към следващият елемент (който същот е изграден от данни и указател)
};

template <typename T>
class LinkedStack{
private:
	StackElement<T>* top; //самата структура от данни съхранява само указател към края на веригата
	void copy(LinkedStack const&);

public:
	// създаване на празен стек
	LinkedStack();

	// конструктор за копиране
	LinkedStack(LinkedStack const&);

	// операция за присвояване
	LinkedStack& operator=(LinkedStack const&);

	// селектори

	// проверка дали стек е празен
	bool empty() const;

	// намиране на елемента на върха на стека
	T peek() const;

	// мутатори

	// включване на елемент
	void push(T const&);

	// изключване на елемент
	T pop();

	// деструктор
	~LinkedStack();
};

template <typename T>
LinkedStack<T>::LinkedStack() {
	top = NULL; //при създаването на нов стек в него няма елементи т.е. веригата е празна
}

template <typename T>
bool LinkedStack<T>::empty() const {
	return top == NULL;
}

template <typename T>
T LinkedStack<T>::peek() const {
	if (empty()) {
		cout << "Грешка: опит за поглеждане в празен стек!\n";
		return 0;
	}

	return top->data;
}

template <typename T>
void LinkedStack<T>::push(T const& x) {
	StackElement<T>* p = new StackElement<T>; //първо създаваме нова кутийка
	p->data = x; //инициализираме данните в зависимост от подадения аргумент
	p->next = top; //насочваме новия елемент към стария край на веригата
	top = p; //новия край на веригата е новия елемент
}

template <typename T>
T LinkedStack<T>::pop() {
	if (empty()) {
		cout << "Грешка: опит за изключване от празен стек!\n";
		return 0;
	}
	// top != NULL
	
	//целта тук е да изтрием последния елемент НО не го правим веднага
	StackElement<T>* p = top; //създаваме указател към последния елемент за да можем да го изтрием
	top = top->next; //насочваме края на веригата към предпоследния елемент
	T x = p->data; //връщаме премахнатия елемент (това може и да не се прави)
	delete p; //изтриваме последния елемент
	return x;
}

template <typename T>
LinkedStack<T>::~LinkedStack() {
	/*
	 * while (!empty())
		pop();
	 */
	//аналогично на логиката при pop()
	StackElement<T>* toDelete;
	while (top != NULL) {
		toDelete = top;
		top = top->next;
		delete toDelete;
	}
	// top == NULL
}

template <typename T>
void LinkedStack<T>::copy(LinkedStack const& ls)
{
	StackElement<T>* toCopy = ls.top; //указател към елемента, който ще копираме
	StackElement<T>* copy; //указател към нов елемент, който трябва да инициализираме и поставим в новия стек
	StackElement<T>* lastCopied = NULL; //указател към последно поставеният елемент за да можем да навържем следващия
	while (toCopy != NULL) {
		copy = new StackElement<T>;

		if (top == NULL) //ако стека е празен насочваме топ към новия елемент
			top = copy;

		copy->data = toCopy->data;

		if (lastCopied != NULL) //ако вече сме откопирали елемент
			lastCopied->next = copy; //насочваме го към новия

		// преместване на указателите
		lastCopied = copy;
		toCopy = toCopy->next;
	}
	lastCopied->next = NULL;	
}

template <typename T>
LinkedStack<T>::LinkedStack(LinkedStack<T> const& ls)
	: top(NULL) {
	//това не работи защото не можем да правим ls.pop() при положение, че ls e const
	/*
	while (!ls.empty()) {
		push(ls.pop());
	}
	*/
		
	//хубав начин за обхождане на елементите на свързана структура без разрушаването ѝ
	//проблема е, че ще се обърне реда на елементите защото структурата е стек
	/*
	StackElement* toCopy = ls.top;
	while(toCopy != NULL) {
		push(toCopy->data);
		toCopy = toCopy->next;
	}
	*/
		
	copy(ls);
	// this->operator=(ls);
	// operator=(ls);
}

template <typename T>
LinkedStack<T>& LinkedStack<T>::operator=(LinkedStack<T> const& ls) {
	if (this != &ls) {
		// !!! ~LinkedStack();
		while (!empty()) pop();//премахваме клетките от стека
		copy(ls);
	}
	return *this;
}

#endif
