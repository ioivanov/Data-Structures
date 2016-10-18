#include <iostream>
using namespace std;

#include "stack.h"

int const EMPTY_STACK = -1; // отбелязваме празен стек

Stack::Stack() {
	topIndex = EMPTY_STACK;
}

bool Stack::empty() const {
	return topIndex == EMPTY_STACK;
}

int Stack::top() const {
	if (empty()) {
		cout << "Грешка: опит за поглеждане в празен стек!\n";
		return 0;
	}

	return a[topIndex];
}

void Stack::push(int const& x) {
	if (full()) {
		cout << "Грешка: опит за включване в пълен стек!\n";
	} else
		a[++topIndex] = x;
}

bool Stack::full() const {
	return topIndex == MAX - 1;
}

int Stack::pop() {
	if (empty()) {
		cout << "Грешка: опит за изключване от празен стек!\n";
		return 0;
	}
	return a[topIndex--];
}
