#include "easyfind.hpp"

#include <iostream>
#include <vector>
#include <list>

template <typename T>
bool check(const T& container, int value, typename T::const_iterator expected, const char* label)
{
    typename T::const_iterator found = easyfind(container, value);
    std::cout << (found == expected ? "[OK] " : "[NG] ") << label << std::endl;
    return (passed);
}

int main()
{
    int values[] = {4, 7, -2, 7, 9};
    const std::vector<int> numbers(values, values + 5);
    std::list<int> linked(values, values + 5);
    const std::vector<int> empty;
    int failures = 0;

    if (!check(numbers, 4, numbers.begin(), "vector: first"))
        ++failures;
    if (!check(numbers, -2, numbers.begin() + 2, "vector: middle and negative"))
        ++failures;
    if (!check(numbers, 9, numbers.end() - 1, "vector: last"))
        ++failures;
    if (!check(numbers, 7, numbers.begin() + 1, "vector: first occurrence"))
        ++failures;
    if (!check(numbers, 42, numbers.end(), "vector: not found"))
        ++failures;
    if (!check(empty, 4, empty.end(), "vector: empty"))
        ++failures;

    std::list<int>::const_iterator first_seven = linked.begin();
    ++first_seven;
    if (!check(linked, 7, first_seven, "list: first occurrence"))
        ++failures;

    std::list<int>::const_iterator negative = first_seven;
    ++negative;
    if (!check(linked, -2, negative, "list: negative"))
        ++failures;
    if (!check(linked, 42, linked.end(), "list: not found"))
        ++failures;

    std::cout << failures << " test(s) failed" << std::endl;
    return (failures != 0);
}
