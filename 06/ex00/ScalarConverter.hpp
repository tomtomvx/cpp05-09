#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

# include <iostream>

enum repry_number
{
	SUCCESS			= 0,
	IMPOSSIBLE		= 1,
	NON_DISPLAYABLE	= 2,
	// PLUS_INF		= 3,
	// MINUS_INF		= 4,
	// NOT_A_NUMBER	= 5
}	;

class ScalarConverter
{
	private:
		static char		_char;
		static int		_int;
		static float	_float;
		static double	_double;

		ScalarConverter();
		ScalarConverter(const ScalarConverter& other);
		ScalarConverter& operator=(const ScalarConverter& other);
		~ScalarConverter();

		static int	StrToDouble(const std::string& given_str);
		static int	StrToFloat(const std::string& given_str);
		static int	StrToInt(const std::string& given_str);
		static int	StrToChar(const std::string& given_str);
		static void	output();

	public:
		static void convert(const std::string& given_str);
}	;

#endif