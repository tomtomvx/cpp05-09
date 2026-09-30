#include <cstddef>
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

void const_test(){
    std::cout << "===const test===" << std::endl;
    unsigned int n = 3;
    Array<int> array(n);
    for (unsigned int i = 0; i < n; i++)
    {
        array[i] = i;
    }
    const Array<int> const_array_copy(array);
    const Array<int> const_array_equal = array;
    for (unsigned int i = 0; i < n; i++)
    {
        std::cout << "const_array_copy[" << i << "] = "  << const_array_copy[i] << std::endl;
        std::cout << "const_array_equal[" << i << "] = "  << const_array_equal[i] << std::endl;
    }
    //const_array_copy[0] = 42;     // compile error
    //const_array_equal[0] = 42;    // compile error 
}

void null_array_test(){
    std::cout << "===null array test===" << std::endl;
    Array<int> array(0);
    try {
        array[0];
        std::cerr << "NG" << std::endl;
    } catch(...) {
        std::cout << "OK" << std::endl;
    }
}

void init_test(){
    std::cout << "===init test===" << std::endl;
    bool flg = true;
    int n = 4;
    Array<int> array(n);
    for (int i = 0; i < n; i++)
    {
        if (array[i] != 0)
        {
            std::cerr << i << ": init failed." << std::endl;
            flg = false;
        }
    }
    std::cout << (flg ? "OK" : "NG") << std::endl;
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
        std::cerr << "Array index out of range:NG" << '\n';
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << ":OK" << '\n';
    }
    try
    {
        numbers[MAX_VAL] = 0;
        std::cerr << "Array index out of range:NG" << '\n';
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << ":OK" << '\n';
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        numbers[i] = rand();
    }
    delete [] mirror;//

	// int *a = new int();
	// std::cout << *a << std::endl;
    deep_copy_test();
    const_test();
    null_array_test();
    init_test();
    return 0;
}