
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <iostream>

Base *generate() { 
	int random_num = rand() % 3; // 0,1,2
	if (random_num == 0)
		return new A;
	else if (random_num == 1)
		return new B;
	else
		return new C;
}
void identify(Base *p) { (void)p; }
void identify(Base &p) { (void)p; }

int main() {
	std::srand(std::time(NULL));
	Base* b = generate(); // A,B,Cいずれかが返される
	(void)b;

	// 禁止されているtypeinfoの確認　デバッグ用
	// if (typeid(*b) == typeid(A))
	// 	std::cout << "A" << std::endl;
	// else if (typeid(*b) == typeid(B))
	// 	std::cout << "B" << std::endl;
	// else if (typeid(*b) == typeid(C))
    //     std::cout << "C" << std::endl;
	return 0; 
}
