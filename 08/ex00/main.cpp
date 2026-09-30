#include "easyfind.hpp"
#include <iostream>
#include <vector>
#include <list>


int main()
{
	// int values[] = {4, 7, -2, 5, 9};
	// const std::vector<int> numbers(values, values + 5);
	// const std::list<int> linked(values, values + 5);

	std::vector<int> numbers;
	numbers.push_back(4);
	numbers.push_back(7);
	numbers.push_back(9);

	std::vector<int>::const_iterator found = easyfind(numbers, 7);

	if (found != numbers.end())
		std::cout << "みつかったよん: " << *found<< std::endl;
	else
		std::cout << "みつからなかたよ；；" << std::endl;

	return (0);
}
