template <typename T>
T dequeueMin(LinkedQueue<T>& q) {
	T min = q.dequeue();
	T sentinel;
	q.enqueue(sentinel);
	while (q.head() != sentinel) {
		T x = q.dequeue();
		if (x < min) {
			q.enqueue(min);
			min = x;
		} else
			q.enqueue(x);
	}
	// махаме сентинела
	q.dequeue();
	return min;
}

template <typename T>
LinkedQueue<T> sortQueue(LinkedQueue<T>& q) {
	LinkedQueue<T> result;
	while (!q.empty())
		result.enqueue(dequeueMin(q));
	return result;
}
