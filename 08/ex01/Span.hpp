#ifndef SPAN_HPP
# define SPAN_HPP

#include <exception>
#include <vector>

class Span {
	private:
		std::vector<int> _v;
		unsigned int _size_max;

	public:
		Span();
		Span(unsigned int n);
		Span(const Span& other);
		Span& operator=(const Span& other);
		~Span();

		void addNumber(int n);
		unsigned int shortestSpan();
		unsigned int longestSpan();

		template <typename InputIterator>
		void addNumber(InputIterator first, InputIterator last)
		{
			std::vector<int> numbers(first, last);

			if (numbers.size() > _size_max - _v.size())
				throw SizeOver();

			_v.insert(_v.end(), numbers.begin(), numbers.end());
		}

		class SizeOver : public std::exception
		{
			public:
				virtual char const *	what() const throw();
		};
}	;

#endif