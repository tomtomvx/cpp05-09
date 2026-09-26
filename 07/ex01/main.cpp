#include "iter.hpp"

#include <iostream>

template<typename T>
void printElement(const T &element) {
	std::cout << element << " ";
}

void addOne(int &element) {
	++element;
}

int main() {
	int numbers[] = {1, 2, 3, 4};
	const std::size_t count = sizeof(numbers) / sizeof(numbers[0]);

	iter(numbers, count, printElement<int>);
	std::cout << std::endl;

	iter(numbers, count, addOne);
	iter(numbers, count, printElement<int>);
	std::cout << std::endl;

	const char *words[] = {"template", "function"};
	iter(words, 2, printElement<const char *>);
	std::cout << std::endl;
	return 0;
}
