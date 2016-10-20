const int MAX = 100;
const int EMPTY_STACK = -1;
template <typename T>
class Stack
{
	T a[MAX];
	int topIndex;
public:
	Stack();
	bool empty() const;
	bool full() const;

	T top() const;
	void push(T const&);
	T pop();
};

template <typename T>
Stack<T>::Stack() : topIndex(EMPTY_STACK) {}

template <typename T>
bool Stack<T>::empty() const
{
	return topIndex == EMPTY_STACK;
}

template <typename T>
bool Stack<T>::full() const
{
	return topIndex == MAX - 1;
}
template <typename T>
T Stack<T>::pop()
{
	if (empty()) {
		std::cout << "Empty stack!\n";
		return T();
	}
	return a[topIndex--];	
}
template <typename T>
void Stack<T>::push(T const& rhs)
{
	if (full()) {
		std::cout << "Full stack!\n";
	}
	else
		a[++topIndex] = rhs;
}

template <typename T>
T Stack<T>:: top() const
{
	if (empty()) {
		std::cout << "Empty stack\n";
		return T();
	}

	return a[topIndex];
}
