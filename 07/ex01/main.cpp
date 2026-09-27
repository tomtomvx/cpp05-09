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

	std::cout << "<< int array test (before addOne) >>" << std::endl << "  ";
	iter(numbers, count, printElement<int>);
	std::cout << std::endl;

	std::cout << "<< int array test (after addOne) >>" << std::endl << "  ";
	iter(numbers, count, addOne);
	iter(numbers, count, printElement<int>);
	std::cout << std::endl;

	const int fixedNumbers[] = {10, 20, 30};
	std::cout << "<< const int array test >>" << std::endl << "  ";
	iter(fixedNumbers, sizeof(fixedNumbers) / sizeof(fixedNumbers[0]), printElement<int>);
	std::cout << std::endl;

	const char *words[] = {"template", "function"};
	std::cout << "<< const char* array test >>" << std::endl << "  ";
	iter(words, 2, printElement<const char *>);
	std::cout << std::endl;
	return 0;
}
