#include "PmergeMe.hpp"

#include <iostream>
#include <exception>

int main(int argc, char** argv)
{
	PmergeMe ins;
	try {
		ins.run(argc, argv);
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}
