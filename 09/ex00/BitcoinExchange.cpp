#include "BitcoinExchange.hpp"

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>

static std::string trim(const std::string& text)
{
	const std::string::size_type start = text.find_first_not_of(" \t\r");
	if (start == std::string::npos)
		return "";
	const std::string::size_type end = text.find_last_not_of(" \t\r");
	return text.substr(start, end - start + 1);
}

static bool isLeapYear(int year)
{
	return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

static bool validDate(const std::string& date)
{
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return false;
	for (std::string::size_type i = 0; i < date.size(); ++i)
	{
		if (i != 4 && i != 7 && (date[i] < '0' || date[i] > '9'))
			return false;
	}
	const int year = std::atoi(date.substr(0, 4).c_str());
	const int month = std::atoi(date.substr(5, 2).c_str());
	const int day = std::atoi(date.substr(8, 2).c_str());
	const int daysInMonth[] = {31, 28, 31, 30, 31, 30,
		31, 31, 30, 31, 30, 31};
	if (year == 0 || month < 1 || month > 12 || day < 1)
		return false;
	int maximum = daysInMonth[month - 1];
	if (month == 2 && isLeapYear(year))
		maximum = 29;
	return day <= maximum;
}

static bool parseNumber(const std::string& text, double& number)
{
	if (text.empty())
		return false;
	bool hasDigit = false;
	for (std::string::size_type i = 0; i < text.size(); ++i)
	{
		const char c = text[i];
		if (c >= '0' && c <= '9')
			hasDigit = true;
		else if (c != '+' && c != '-' && c != '.' && c != 'e' && c != 'E')
			return false;
	}
	if (!hasDigit)
		return false;
	char* end = NULL;
	number = std::strtod(text.c_str(), &end);
	return end != text.c_str() && *end == '\0';
}

BitcoinExchange::BitcoinExchange()
{
	loadDatabase("data.csv");
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _rates(other._rates)
{
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		_rates = other._rates;
	return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::loadDatabase(const std::string& path)
{
	std::ifstream file(path.c_str());
	if (!file)
		throw std::runtime_error("Error: could not open database.");
	std::string line;
	if (!std::getline(file, line) || trim(line) != "date,exchange_rate")
		throw std::runtime_error("Error: invalid database header.");
	while (std::getline(file, line))
	{
		const std::string::size_type comma = line.find(',');
		if (comma == std::string::npos || line.find(',', comma + 1) != std::string::npos)
			throw std::runtime_error("Error: invalid database row.");
		const std::string date = trim(line.substr(0, comma));
		const std::string rateText = trim(line.substr(comma + 1));
		double rate = 0;
		if (!validDate(date) || !parseNumber(rateText, rate)
			|| rate < 0 || rate > std::numeric_limits<double>::max()
			|| !_rates.insert(std::make_pair(date, rate)).second)
			throw std::runtime_error("Error: invalid database row.");
	}
	if (file.bad() || _rates.empty())
		throw std::runtime_error("Error: could not read database.");
}

void BitcoinExchange::processLine(const std::string& line) const
{
	const std::string::size_type bar = line.find('|');
	if (bar == std::string::npos || line.find('|', bar + 1) != std::string::npos)
	{
		std::cerr << "Error: bad input => " << line << std::endl;
		return;
	}
	const std::string date = trim(line.substr(0, bar));
	const std::string valueText = trim(line.substr(bar + 1));
	double value = 0;
	if (!validDate(date) || !parseNumber(valueText, value))
	{
		std::cerr << "Error: bad input => " << line << std::endl;
		return;
	}
	if (value < 0)
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return;
	}
	if (value > 1000)
	{
		std::cerr << "Error: too large a number." << std::endl;
		return;
	}
	std::map<std::string, double>::const_iterator rate = _rates.upper_bound(date);
	if (rate == _rates.begin())
	{
		std::cerr << "Error: bad input => " << line << std::endl;
		return;
	}
	--rate;
	std::cout << std::setprecision(10) << date << " => " << value
		<< " = " << value * rate->second << std::endl;
}

void BitcoinExchange::processFile(const std::string& path) const
{
	std::ifstream file(path.c_str());
	if (!file)
		throw std::runtime_error("Error: could not open file.");
	std::string line;
	bool firstLine = true;
	while (std::getline(file, line))
	{
		if (firstLine && trim(line) == "date | value")
		{
			firstLine = false;
			continue;
		}
		firstLine = false;
		processLine(line);
	}
	if (file.bad())
		throw std::runtime_error("Error: could not read file.");
}
