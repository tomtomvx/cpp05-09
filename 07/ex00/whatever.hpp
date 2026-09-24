#ifndef WHATEVER_HPP
# define WHATEVER_HPP

/*
template <typename T>
T add(T a, T b) {
	return a + b;
}
*/

template <typename T>
void swap(T &a, T &b){
	T tmp = a;
	a = b;
	b = tmp;
}

template <typename T>
T min(T a, T b){
	return a < b ? a : b;
}

#endif
