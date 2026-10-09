#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <exception>
# include <iostream>
# include <string>
# include <vector>
# include <list>

class PmergeMe {
	private:
		// 入力とソートに使う2種類のコンテナを保持する。
		std::vector<int>	_vec;
		std::list<int>		_lst;
		// ソート順を決める比較だけを、それぞれ別に数える。
		size_t				_vecComparisons;
		size_t				_lstComparisons;

		std::vector<int>	_parseInput(int argc, char** argv);
		std::vector<int>	_getInsertionOrder(size_t n);
		std::vector<int>	_sortVector(std::vector<int> input);
		std::list<int>		_sortList(std::list<int> input);
		template <typename Container>
		void				_printContainer(const std::string& label, const Container& c);

	public:
		class				PmergeMeError : public std::exception {
							private:
								std::string _detail;

							public:
								PmergeMeError();
								PmergeMeError(const std::string& detail);
								PmergeMeError(const PmergeMeError& other);
								PmergeMeError& operator=(const PmergeMeError& other);
								~PmergeMeError() throw();

								const char*	what() const throw();
		}	;

							PmergeMe();
							PmergeMe(const PmergeMe& other);
							PmergeMe& operator=(const PmergeMe& other);
							~PmergeMe();

		void				run(int argc, char** argv);
}	;

template <typename Container>
void PmergeMe::_printContainer(const std::string& label, const Container& c) {
	// vector/list のどちらも同じ表示形式にする。型に依存する iterator には typename が必要。
	std::cout << label;
	for (typename Container::const_iterator it = c.begin(); it != c.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

#endif
