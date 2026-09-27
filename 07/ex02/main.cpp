#include <iostream>
#include "Array.hpp"

#define MAX_VAL 750

void deep_copy_test()
{
    std::cout << "===deep_copy_test===" << std::endl;
    unsigned int n = 5;
    Array<int> numbers(n);
    for (unsigned int i = 0; i < n; i++)
    {
        numbers[i] = i;
    }
    Array<int> except(numbers);
    numbers[2] =  42;
    if (except[2] == 42)
        std::cerr << "The values in another array have been updated!!" << std::endl;
    else
        std::cout << "OK" << std::endl;
}

int main(int, char**)
{
    Array<int> numbers(MAX_VAL);
    int* mirror = new int[MAX_VAL];
    srand(time(NULL));
    for (int i = 0; i < MAX_VAL; i++)
    {
        const int value = rand();
        numbers[i] = value;
        mirror[i] = value;
    }
    //SCOPE
    {
        Array<int> tmp = numbers;
        Array<int> test(tmp);
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        if (mirror[i] != numbers[i])
        {
            std::cerr << "didn't save the same value!!" << std::endl;
            return 1;
        }
    }
    try
    {
        numbers[-2] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        numbers[MAX_VAL] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        numbers[i] = rand();
    }
    delete [] mirror;//

	// int *a = new int();
	// std::cout << *a << std::endl;
    deep_copy_test();

    return 0;
}