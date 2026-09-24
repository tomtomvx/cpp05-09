#include <iostream>
#include <string>
#include "whatever.hpp"

class Test {
	private:
		int _number;
	public:
		Test(int number);
		int getNumber() const;
		bool operator<(const Test& other) const;
		bool operator>(const Test& other) const;
};

Test::Test(int number) : _number(number){}
int Test::getNumber() const { return _number; }
bool Test::operator<(const Test& other) const {
	return this->_number < other.getNumber();
}
bool Test::operator>(const Test& other) const {
	return this->_number > other.getNumber();
}

std::ostream& operator<<(std::ostream& os, const Test& t) {
    os << t.getNumber();
    return os;
}

void custom_class_compare_test(){
	Test A(5);
	Test B(7);

	::swap(A, B);
	std::cout << "===custom_class_compare_test===" << std::endl;
	std::cout << "A = " << A << ", B = " << B<< std::endl;	
	std::cout << "min( a, b ) = " << ::min(A, B) << std::endl;
	std::cout << "max( a, b ) = " << ::max(A, B) << std::endl;
	std::cout << std::endl;
}

void equal_paramator_test(){
	int a = 42;
	int b = 42;

	std::cout << "===equal_paramator_test===" << std::endl;
	std::cout << "a = " << &a << ", b = " << &b << std::endl;	
	std::cout << "min( a, b ) = " << &::min(a, b) << std::endl;
	std::cout << "max( a, b ) = " << &::max(a, b) << std::endl;
	std::cout << std::endl;
}

void const_test(){
	int a = 1;
	const int b = 3;
	std::cout << "===const_test===" << std::endl;
	std::cout << "a = " << a << ", b = " << b << std::endl;
	std::cout << "min( 4, 2 ) = " << ::min(4, 2) << std::endl;
	std::cout << "max( 4, 2 ) = " << ::max(4, 2) << std::endl;
	std::cout << "min( a, b ) = " << ::min(a, b) << std::endl;
	std::cout << "max( a, b ) = " << ::max(a, b) << std::endl;
	std::cout << std::endl;	
}

int main(void) {
	int a = 2;
	int b = 3;
	::swap(a, b);
	std::cout << "a = " << a << ", b = " << b << std::endl;
	std::cout << "min( a, b ) = " << ::min(a, b) << std::endl;
	std::cout << "max( a, b ) = " << ::max(a, b) << std::endl;
	std::string c = "chaine1";
	std::string d = "chaine2";
	::swap(c, d);
	std::cout << "c = " << c << ", d = " << d << std::endl;
	std::cout << "min( c, d ) = " << ::min(c, d) << std::endl;
	std::cout << "max( c, d ) = " << ::max(c, d) << std::endl;

	custom_class_compare_test();
	equal_paramator_test();
	const_test();
	return 0;
}
