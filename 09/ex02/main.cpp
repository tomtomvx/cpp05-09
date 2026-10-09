#include "PmergeMe.hpp"

#include <iostream>
#include <exception>

int main(int argc, char** argv)
{
	PmergeMe ins;
	// 入力・ソート中のエラーは標準エラーに出し、終了コード 1 を返す。
	try {
		ins.run(argc, argv);
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}
