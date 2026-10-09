#include "BitcoinExchange.hpp"

#include <exception>
#include <iostream>

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}
	try
	{
		BitcoinExchange exchange;
		exchange.processFile(argv[1]);
	}
	catch (const std::exception& error)
	{
		std::cerr << error.what() << std::endl;
		return 1;
	}
	return 0;
}
