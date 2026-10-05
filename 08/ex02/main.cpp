#include "MutantStack.hpp"

#include <iostream>
#include <list>

static bool check(bool condition, const char *label)
{
	std::cout << (condition ? "[OK] " : "[NG] ") << label << std::endl;
	return (condition);
}

static bool sameValues(const MutantStack<int>& stack, const std::list<int>& list)
{
	MutantStack<int>::const_iterator stackIt = stack.begin();
	std::list<int>::const_iterator listIt = list.begin();

	while (stackIt != stack.end() && listIt != list.end())
	{
		if (*stackIt != *listIt)
			return (false);
		++stackIt;
		++listIt;
	}
	return (stackIt == stack.end() && listIt == list.end());
}

static void fillValues(MutantStack<int>& stack, std::list<int>& list)
{
	const int values[] = {5, 3, 5, 737, 0};
	for (std::size_t i = 0; i < sizeof(values) / sizeof(values[0]); ++i)
	{
		stack.push(values[i]);
		list.push_back(values[i]);
	}
}

/*   push, top, pop, sizeが通常のスタックとして動くか確認   */
static int testStackOperations()
{
	MutantStack<int> stack;
	int failures = 0;

	stack.push(5);
	stack.push(17);
	failures += !check(stack.top() == 17, "top after push");
	stack.pop();
	failures += !check(stack.top() == 5 && stack.size() == 1,
		"top and size after pop");
	return (failures);
}

/*   begin()からend()までたどり、std::listと同じ順序で値を読めるか確認。表示される順序は、積んだ順の5, 3, 5, 737, 0   */
static int testIteration()
{
	MutantStack<int> stack;
	std::list<int> list;
	fillValues(stack, list);

	std::cout << "MutantStack: ";
	for (MutantStack<int>::iterator it = stack.begin(); it != stack.end(); ++it)
		std::cout << *it << ' ';
	std::cout << std::endl;
	std::cout << "std::list:   ";
	for (std::list<int>::iterator it = list.begin(); it != list.end(); ++it)
		std::cout << *it << ' ';
	std::cout << std::endl;
	return (!check(sameValues(stack, list), "same iteration order as list"));
}

/*   コピーコンストラクタで値がコピーされ、constなコピーでも走査できるか確認   */
static int testCopy()
{
	MutantStack<int> stack;
	std::list<int> list;
	fillValues(stack, list);
	const MutantStack<int> copied(stack);
	return (!check(sameValues(copied, list), "copy and const iteration"));
}

/*   代入で既存の値が置き換わるか、自己代入assigned = *selfでも値が保たれるか確認   */
static int testAssignment()
{
	MutantStack<int> stack;
	std::list<int> list;
	fillValues(stack, list);
	MutantStack<int> assigned;
	int failures = 0;

	assigned.push(-1);
	assigned = stack;
	failures += !check(sameValues(assigned, list), "assignment");
	MutantStack<int>* self = &assigned;
	assigned = *self;
	failures += !check(sameValues(assigned, list), "self-assignment");
	return (failures);
}

/*   空のスタックではbegin() == end()になるか確認   */
static int testEmpty()
{
	MutantStack<int> empty;
	return (!check(empty.begin() == empty.end(), "empty iteration"));
}

int main()
{
	int failures = 0;

	failures += testStackOperations();
	failures += testIteration();
	failures += testCopy();
	failures += testAssignment();
	failures += testEmpty();
	std::cout << failures << " test(s) failed" << std::endl;
	return (failures != 0);
}
