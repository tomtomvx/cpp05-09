
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <iostream>

Base *generate() { 
	int random_num = std::rand() % 3;
	if (random_num == 0)
		return new A;
	else if (random_num == 1)
		return new B;
	else
		return new C;
}

void identify(Base *p) { 
	if (dynamic_cast<A*>(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C*>(p))
        std::cout << "C" << std::endl;
}

void identify(Base &p) {
	try {
		static_cast<void>(dynamic_cast<A&>(p));
		std::cout << "A" << std::endl;
		return ;
	} catch (...) {
		
	}
	try {
		static_cast<void>(dynamic_cast<B&>(p));
		std::cout << "B" << std::endl;
		return ;
	} catch (...) {
		
	}
	try {
		static_cast<void>(dynamic_cast<C&>(p));
		std::cout << "C" << std::endl;
		return ;
	} catch (...) {
		
	}
}

int main() {
	std::srand(std::time(NULL));
	Base* b = generate();
	identify(b);
	identify(*b);
	delete b;
	return 0;
}
