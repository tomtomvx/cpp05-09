#include "PmergeMe.hpp"

#include <iostream>
#include <cstdlib>
#include <climits>
#include <utility>
#include <cerrno>
#include <ctime>
#include <algorithm>
#include <vector>
#include <list>

namespace {
	// コピーされても同じカウンタを指すため、lower_bound 内の比較も集計できる。
	struct CountingLess {
		size_t* _count;

		explicit CountingLess(size_t& count) : _count(&count) {}

		bool operator()(int left, int right) const {
			++(*_count);
			return left < right;
		}
	};
}


// 例外の定型操作。詳細文言は DEBUG ビルド時だけ what() から返す。
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
	// Jacobsthal 数列を境界にして、各区間の添字を大きい方から並べる。
	// 小さい値 b1 は先に挿入するため、返す順序の先頭は b1 の添字 0。
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
		// 例: b1, b3, b2, b5, b4, ... の順に挿入対象を選ぶ。
		int hi = std::min(jacobsthal[k], nInt);
		int lo = jacobsthal[k - 1] + 1;
		for (int i = hi; i >= lo; --i) {
			order.push_back(i);
		}
	}
	// 上では b1 始まりで組み立て、ここでコンテナ用の 0 始まりに直す。
	for (size_t i = 0; i < order.size(); ++i) order[i] -= 1;
	return order;
}

std::vector<int> PmergeMe::_parseInput(int argc, char** argv) {
	// 各引数は符号なしの数字列かつ int の正の範囲に収まることを確認する。
	// strtol 前の文字検査で空白・符号・小数点を除外する。
	if (argc < 2)
		throw PmergeMeError("_perceInput::Insufficient arguments");

	std::vector<int> values;
	for (int i = 1; i < argc; ++i) {
		std::string token = argv[i];
		if (token.empty())
			throw PmergeMeError("_perceInput::Not a number");
		for (size_t j = 0; j < token.size(); ++j) {
			if (token[j] < '0' || token[j] > '9')
				throw PmergeMeError("_perceInput::Contains invalid characters");
		}
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
		values.push_back(static_cast<int>(value));
	}
	return values;
}

std::vector<int> PmergeMe::_sortVector(std::vector<int> input) {
	// Ford-Johnson: ペアの大きい値を再帰的に並べ、小さい値を後から挿入する。
	if (input.size() <= 1) return input;
	CountingLess less(_vecComparisons);
	// 奇数個なら末尾を一時的に外し、最後の挿入候補に含める。
	bool hasStraggler = false;
	int straggler = 0;
	if (input.size() % 2 == 1) {
		hasStraggler = true;
		straggler = input.back();
		input.pop_back();
	}
	std::vector<std::pair<int, int> > pairs;
	// pair(first, second) は常に first >= second。
	for (size_t i = 0; i + 1 < input.size(); i += 2) {
		if (less(input[i + 1], input[i]))
			pairs.push_back(std::make_pair(input[i], input[i + 1]));
		else
			pairs.push_back(std::make_pair(input[i + 1], input[i]));
	}
	std::vector<int> bigs;
	for (size_t i = 0; i < pairs.size(); ++i)
		bigs.push_back(pairs[i].first);
	// 大きい値だけを再帰ソートする。各小さい値との対応は次で復元する。
	std::vector<int> sortedChain = _sortVector(bigs);
	std::vector<std::pair<int, int> > sortedPairs;
	std::vector<bool> used(pairs.size(), false);
	// 同じ大きい値が複数あっても、各ペアを一度ずつ選ぶ。
	for (size_t i = 0; i < sortedChain.size(); ++i) {
		size_t j = 0;
		while (j < pairs.size() &&
			(used[j] || pairs[j].first != sortedChain[i]))
			++j;
		if (j == pairs.size())
			throw PmergeMeError("_sortVector::Pair not found");
		sortedPairs.push_back(pairs[j]);
		used[j] = true;
	}
	// a1 は大きい値の最小値で、b1 <= a1 なので b1 を先頭に置ける。
	sortedChain.insert(sortedChain.begin(), sortedPairs[0].second);
	std::vector<int> order = _getInsertionOrder(
		sortedPairs.size() + (hasStraggler ? 1 : 0));
	// 残りの小さい値を Jacobsthal 順で挿入する。b1 は挿入済み。
	for (size_t i = 1; i < order.size(); ++i) {
		size_t index = static_cast<size_t>(order[i]);
		int smallVal = straggler;
		std::vector<int>::iterator bigPos = sortedChain.end();
		if (index < sortedPairs.size()) {
			smallVal = sortedPairs[index].second;
			// 相方の大きい値より前だけを探す。余りの値には相方がない。
			bigPos = std::find(sortedChain.begin(), sortedChain.end(),
					sortedPairs[index].first);
		}
		// vector は二分探索で位置を決めるが、挿入時に後続要素を移動する。
		std::vector<int>::iterator insertPos =
			std::lower_bound(sortedChain.begin(), bigPos, smallVal,
				less);
		sortedChain.insert(insertPos, smallVal);
	}
	return sortedChain;
}

std::list<int> PmergeMe::_sortList(std::list<int> input) {
	// list 版もペア化・大きい値の再帰ソート・小さい値の挿入を独立して行う。
	if (input.size() <= 1) return input;
	CountingLess less(_lstComparisons);

	// 奇数個の余りはペアを作らず、最後の挿入候補として扱う。
	bool hasStraggler = false;
	int straggler = 0;
	if (input.size() % 2 == 1) {
		hasStraggler = true;
		straggler =input.back();
		input.pop_back();
	}

	std::vector<std::pair<int, int> > pairs;
	std::list<int>::iterator it = input.begin();

	// list は添字アクセスできないため、イテレータを2つずつ進めてペアを作る。
	while (it != input.end()) {
		std::list<int>::iterator first = it++;
		std::list<int>::iterator second = it++;

		if (less(*second, *first))
			pairs.push_back(std::make_pair(*first, *second));
		else
			pairs.push_back(std::make_pair(*second, *first));
	}

	std::list<int> bigs;
	for (size_t i = 0; i < pairs.size(); ++i)
		bigs.push_back(pairs[i].first);
	// 再帰後の大きい値の順に、未使用の元ペアを対応付ける。
	std::list<int> sortedChain = _sortList(bigs);
	std::vector<std::pair<int, int> > sortedPairs;
	std::vector<bool> used(pairs.size(), false);
	for (std::list<int>::const_iterator it = sortedChain.begin();
		it != sortedChain.end(); ++it) {
		size_t j = 0;
		while (j < pairs.size() && (used[j] || pairs[j].first != *it))
			++j;
		if (j == pairs.size())
			throw PmergeMeError("_sortList::Pair not found");
		sortedPairs.push_back(pairs[j]);
		used[j] = true;
	}
	// b1 を先頭に置き、残りを vector 版と同じ順序で挿入する。
	sortedChain.insert(sortedChain.begin(), sortedPairs[0].second);
	std::vector<int> order = _getInsertionOrder(
		sortedPairs.size() + (hasStraggler ? 1 : 0));
	for (size_t i = 1; i < order.size(); ++i) {
		size_t index = static_cast<size_t>(order[i]);
		int smallVal = straggler;
		std::list<int>::iterator bigPos = sortedChain.end();
		if (index < sortedPairs.size()) {
			smallVal = sortedPairs[index].second;
			// 探索範囲は相方の大きい値の直前まで。余りには範囲制限がない。
			bigPos = std::find(sortedChain.begin(), sortedChain.end(),
					sortedPairs[index].first);
		}
		// list の lower_bound は線形走査だが、位置が決まれば挿入は定数時間。
		std::list<int>::iterator insertPos =
			std::lower_bound(sortedChain.begin(), bigPos, smallVal,
				less);
		sortedChain.insert(insertPos, smallVal);
	}
	return sortedChain;
}


// デフォルト構築では空の状態。コピー・代入ではコンテナと比較回数を複製する。
PmergeMe::PmergeMe() : _vecComparisons(0), _lstComparisons(0) {}
PmergeMe::PmergeMe(const PmergeMe& other)
	: _vec(other._vec), _lst(other._lst),
	  _vecComparisons(other._vecComparisons),
	  _lstComparisons(other._lstComparisons) {}
PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
	if (&other != this) {
		_vec = other._vec;
		_lst = other._lst;
		_vecComparisons = other._vecComparisons;
		_lstComparisons = other._lstComparisons;
	}
	return *this;
}
PmergeMe::~PmergeMe() {}


void PmergeMe::run(int argc, char** argv) {
	// 共通の入力を一度検証し、両コンテナを同じ数列で比較する。
	std::vector<int> values = _parseInput(argc, argv);
	// run を繰り返しても、毎回その入力だけの比較回数を表示する。
	_vecComparisons = 0;
	_lstComparisons = 0;

	// 計測範囲には各コンテナへの格納とソートを含める。
	clock_t stVec = std::clock();
	_vec.assign(values.begin(), values.end());
	std::vector<int> sortedVec = _sortVector(_vec);
	clock_t edVec = std::clock();

	clock_t stLst = std::clock();
	_lst.assign(values.begin(), values.end());
	std::list<int> sortedLst = _sortList(_lst);
	clock_t edLst = std::clock();

	// 2つの実装が同じ結果を返したことを表示前に確認する。
	if (sortedVec.size() != sortedLst.size() ||
		!std::equal(sortedVec.begin(), sortedVec.end(), sortedLst.begin())) {
		throw PmergeMeError("run::vector and list results mismatch");
	}

	// clock() の CPU 時間をマイクロ秒に換算する。
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
	// 比較回数を見たいときは次の2行を有効にする。ペア検索・結果照合は対象外。
	// std::cerr << "Comparisons with std::vector: " << _vecComparisons << std::endl;
	// std::cerr << "Comparisons with std::list: " << _lstComparisons << std::endl;
}
