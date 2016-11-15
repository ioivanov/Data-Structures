template <typename T>
using binop = T (*)(T, T);

template <typename T>
using unop = T (*)(T);

template <typename T>
using pred = bool (*)(T);

template <typename T, typename I, typename binop>
T foldr(binop op, T nv, I it) {
	if (!it)
		return nv;
	T x = *it++;
	return op(x, foldr(op, nv, it));
}

template <typename T, typename I, typename binop>
T foldl(binop op, T nv, I it) {
	T result = nv;
	while(it)
		result = op(result,*it++);
	return result;
}

template <typename I, typename unop>
void map(unop f, I it) {
	for(;it;++it)
		*it = f(*it);
}

template <typename T, typename I, typename pred>
void filter(pred p, List<T, I>& l) {
	I it = l.begin();
	while (it) {
		if (!p(*it)) {
			T tmp;
			I toDelete = it;
			++it;
			l.deleteAt(tmp, toDelete);
		}
		else
			++it;
	}
}
