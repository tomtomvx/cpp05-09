#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

# include <string>

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
		static int	StrToFloat(bool is_float);
		static int	StrToInt();
		static int	StrToChar();
		static void	output(int char_status, int int_status,
							int float_status, int double_status);

	public:
		static void convert(const std::string& given_str);
};

#endif
