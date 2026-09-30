#ifndef SPAN_HPP
# define SPAN_HPP

#include <exception>
#include <vector>

class Span {
	private:
		std::vector<int> _v;
		unsigned int _size_max;

	public:
		class SizeOver : public std::exception
		{
		public:
			virtual char const *	what() const throw();
		};

		Span();
		Span(unsigned int n);
		Span(Span& other);
		Span& operator=(Span& other);
		~Span();

		void addNumber(int n);
		int shortestSpan();
		int longestSpan();
};

#endif