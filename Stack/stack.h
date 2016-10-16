#ifndef STACK_H_
#define STACK_H_

int const MAX = 100;

class Stack {
private:
	int a[MAX];	// елементите на стека
	int top;	// индекс на последния елемент

	// проверка дали стек е пълен
	bool full() const;

public:

	// създаване на празен стек
	Stack();

	// селектори

	// проверка дали стек е празен
	bool empty() const;

	// намиране на елемента на върха на стека
	int peek() const;

	// мутатори

	// включване на елемент
	void push(int const&);

	// изключване на елемент
	int pop();
};

#endif /* STACK_H_ */
