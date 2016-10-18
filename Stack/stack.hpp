const int MAX = 100;
const int EMPTY_STACK = -1;
template <class T>
class Stack
{
	T a[MAX];
	int m_top;
public:
	Stack();
	bool empty() const;
	bool full() const;

	T top() const;
	void push(T const&);
	T pop();
	int getIdx() const { return m_top; }
};

template <class T>
Stack<T>::Stack() : m_top(EMPTY_STACK) {}

template <class T>
bool Stack<T>::empty() const
{
	return m_top == EMPTY_STACK;
}

template <class T>
bool Stack<T>::full() const
{
	return m_top == MAX - 1;
}
template <class T>
T Stack<T>::pop()
{
	if (empty()) {
		std::cout << "Грешка: опит за изключване от празен стек!\n";
		return 0;
	}
	return a[m_top--];	
}
template <class T>
void Stack<T>::push(T const& rhs)
{
	if (full()) {
		std::cout << "full stack!\n";
	}
	else
		a[++m_top] = rhs;
}

template <class T>
T Stack<T>:: top() const
{
	if (empty()) {
		std::cout << "Грешка: опит за поглеждане в празен стек!\n";
		return 0;
	}

	return a[m_top];
}
