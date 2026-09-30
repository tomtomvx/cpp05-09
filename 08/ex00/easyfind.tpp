// #include "easyfind.hpp"
#include <algorithm>

template <typename T>
typename T::const_iterator easyfind(const T& container, int value)
{
	return (std::find(container.begin(), container.end(), value));
}
