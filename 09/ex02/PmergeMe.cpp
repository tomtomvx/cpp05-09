#include "PmergeMe.hpp"

#include <iostream>
#include <cerrno>

#include <algorithm>

#include <vector>
#include <list>


PmergeMe::PmergeMeError::PmergeMeError() : _detail("Error") {}

PmergeMe::PmergeMeError::PmergeMeError(const std::string& detail)
    : _detail(detail) {}

PmergeMe::PmergeMeError::PmergeMeError(const PmergeMeError& other)
    : _detail(other._detail) {}

PmergeMe::PmergeMeError& PmergeMe::PmergeMeError::operator=(
    const PmergeMeError& other) {
    if (&other != this) {
        _detail = other._detail;
    }
    return *this;
}

PmergeMe::PmergeMeError::~PmergeMeError() throw() {}

const char* PmergeMe::PmergeMeError::what() const throw() {
#ifdef DEBUG
    return _detail.c_str();
#else
    return "Error";
#endif
}


std::vector<int> PmergeMe::_getInsertionOrder(size_t n) {
	int nInt = static_cast<int>(n);
	std::vector<int> jacobsthal;
	jacobsthal.push_back(1);
	jacobsthal.push_back(1);
	while (jacobsthal.back() < nInt) {
		int next = jacobsthal[jacobsthal.size() - 1] +
				   2 * jacobsthal[jacobsthal.size() - 2];
		jacobsthal.push_back(next);
	}

	std::vector<int> order;
	if (n == 0) return order;
	order.push_back(1);

	for (size_t k = 2; k < jacobsthal.size(); ++k) {
		int hi = std::min(jacobsthal[k], nInt);
		int lo = jacobsthal[k - 1] + 1;
		for (int i = hi; i >= lo; --i) {
			order.push_back(i);
		}
	}
	for (size_t i = 0; i < order.size(); ++i) order[i] -= 1;
	return order;
}

void PmergeMe::_parseInput(int argc, char** argv) {
	if (argc < 2)
		throw PmergeMeError("_perceInput::Insufficient arguments");

	for (int i = 1; i < argc; ++i) {
		std::string token = argv[i];
		char* endptr;
		errno = 0;
		long value = std::strtol(token.c_str(), &endptr, 10);

		if (endptr == token.c_str())
			throw PmergeMeError("_perceInput::Not a number");
		if (*endptr != '\0')
			throw PmergeMeError("_perceInput::Contains invalid characters");
		if (errno == ERANGE)
			throw PmergeMeError("_perceInput::Numbers greater than long");
		if (value <= 0)
			throw PmergeMeError("_perceInput::Not a natural number");
		if (value > INT_MAX)
			throw PmergeMeError("_perceInput::Exceeded the maximum value for int");
		_vec.push_back(static_cast<int>(value));
		_lst.push_back(static_cast<int>(value));
	}
}

std::vector<int> PmergeMe::_sortVector(std::vector<int> input) {
	if (input.size() <= 1) return input;
	bool hasStraggler = false;
	int straggler = 0;
	if (input.size() % 2 == 1) {
		hasStraggler = true;
		straggler = input.back();
		input.pop_back();
	}
	std::vector<std::pair<int, int> > pairs;
	for (size_t i = 0; i + 1 < input.size(); i += 2) {
		if (input[i] > input[i + 1])
			pairs.push_back(std::make_pair(input[i], input[i + 1]));
		else
			pairs.push_back(std::make_pair(input[i + 1], input[i]));
	}
	std::vector<int> bigs;
	for (size_t i = 0; i < pairs.size(); ++i)
		bigs.push_back(pairs[i].first);
	std::vector<int> sortedChain = _sortVector(bigs);
	std::vector<int> order = _getInsertionOrder(pairs.size());
	for (size_t i = 0; i < order.size(); ++i) {
		int smallVal = pairs[order[i]].second;
		int pairedBig = pairs[order[i]].first;
		std::vector<int>::iterator bigPos =
			std::find(sortedChain.begin(), sortedChain.end(), pairedBig);
		std::vector<int>::iterator insertPos =
			std::lower_bound(sortedChain.begin(), bigPos, smallVal);
		sortedChain.insert(insertPos, smallVal);
	}
	if (hasStraggler) {
		std::vector<int>::iterator insertPos =
			std::lower_bound(sortedChain.begin(), sortedChain.end(), straggler);
		sortedChain.insert(insertPos, straggler);
	}
	return sortedChain;
}

std::list<int> PmergeMe::_sortList(std::list<int> input) {
	if (input.size() <= 1) return input;

	bool hasStraggler = false;
	int straggler = 0;
	if (input.size() % 2 == 1) {
		hasStraggler = true;
		straggler =input.back();
		input.pop_back();
	}

	std::vector<std::pair<int, int> > pairs;
	std::list<int>::iterator it = input.begin();

	while (it != input.end()) {
		std::list<int>::iterator first = it++;
		std::list<int>::iterator second = it++;

		if (*first > *second)
			pairs.push_back(std::make_pair(*first, *second));
		else
			pairs.push_back(std::make_pair(*second, *first));
	}

	std::list<int> bigs;
	for (size_t i = 0; i < pairs.size(); ++i)
		bigs.push_back(pairs[i].first);
	std::list<int> sortedChain = _sortList(bigs);
	std::vector<int> order = _getInsertionOrder(pairs.size());
	for (size_t i = 0; i < order.size(); ++i) {
		int smallVal = pairs[order[i]].second;
		int pairedBig = pairs[order[i]].first;
		std::list<int>::iterator bigPos =
			std::find(sortedChain.begin(), sortedChain.end(), pairedBig);

		// std::list<int>::iterator insertPos = sortedChain.begin();
		// while (insertPos != bigPos && *insertPos < smallVal)
		// 	++insertPos;
		std::list<int>::iterator insertPos =
		std::lower_bound(sortedChain.begin(), bigPos, smallVal);
		sortedChain.insert(insertPos, smallVal);
	}
	if (hasStraggler) {
		std::list<int>::iterator insertPos = sortedChain.begin();
		while (insertPos != sortedChain.end() && *insertPos < straggler)
			++insertPos;
		sortedChain.insert(insertPos, straggler);
	}
	return sortedChain;
}


PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe& other) :_vec(other._vec), _lst(other._lst) {}
PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
	if (&other != this) {
		_vec = other._vec;
		_lst = other._lst;
	}
	return *this;
}
PmergeMe::~PmergeMe() {}


void PmergeMe::run(int argc, char** argv) {
	_parseInput(argc, argv);

	clock_t stVec = std::clock();
	std::vector<int> sortedVec = _sortVector(_vec);
	clock_t edVec = std::clock();

	clock_t stLst = std::clock();
	std::vector<int> sortedLst = _sortList(_lst);
	clock_t edLst = std::clock();

	if (sortedVec.size() != sortedLst.size() ||
		!std::equal(sortedVec.begin(), sortedVec.end(), sortedLst.begin())) {
		throw PmergeMeError("run::vector and list results mismatch");
	}

	double elapsedVecUs =
		static_cast<double>(edVec - stVec) / CLOCKS_PER_SEC * 1000000.0;
	double elapsedLstUs =
		static_cast<double>(edLst - stLst) / CLOCKS_PER_SEC * 1000000.0;

	_printContainer("Before:\t", _vec);
	_printContainer("After:\t", sortedVec);
	std::cout << "Time to process a range of "<< _vec.size()
			  << " elements with std::[vector] : " << elapsedVecUs << " us"
			  << std::endl;
	std::cout << "Time to process a range of "<< _lst.size()
			  << " elements with std::[list] : " << elapsedLstUs << " us"
			  << std::endl;
}
