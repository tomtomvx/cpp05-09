#include "ScalarConverter.hpp"
#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <limits>
#include <sstream>
#include <iostream>

namespace
{
	enum status
	{
		SUCCESS,
		IMPOSSIBLE,
		NON_DISPLAYABLE
	};

	std::string formatNumber(double value)
	{
		if (value != value)
			return ("nan");
		if (value == std::numeric_limits<double>::infinity())
			return ("+inf");
		if (value == -std::numeric_limits<double>::infinity())
			return ("-inf");
		std::ostringstream out;
		out << value;
		std::string result = out.str();
		if (result.find_first_of(".eE") == std::string::npos)
			result += ".0";
		return (result);
	}
}

char	ScalarConverter::_char;
int		ScalarConverter::_int;
float	ScalarConverter::_float;
double	ScalarConverter::_double;

ScalarConverter::ScalarConverter()
{
}

ScalarConverter::ScalarConverter(const ScalarConverter& other)
{
	(void)other;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other)
{
	(void)other;
	return (*this);
}

ScalarConverter::~ScalarConverter()
{
}

int	ScalarConverter::StrToDouble(const std::string& given_str)
{
	const char* str = given_str.c_str();
	char* endptr;

	errno = 0;
	double value = std::strtod(str, &endptr);

	// if ((errno == ERANGE) && (value == HUGE_VAL || value == -HUGE_VAL))
	// 	return (IMPOSSIBLE);
	// if (endptr == str)
	// 	return (IMPOSSIBLE);
	// if ((*endptr != '\0') && !(*endptr == 'f' && endptr[1] == '\0'))
	// 	return (IMPOSSIBLE);

	if (((errno == ERANGE) && (value == HUGE_VAL || value == -HUGE_VAL)) ||
		endptr == str ||
		(*endptr != '\0' && !(*endptr == 'f' && endptr[1] == '\0')))
		return (IMPOSSIBLE);

	_double = value;
	return (SUCCESS);
}

int	ScalarConverter::StrToFloat(bool is_float)
{
	double infinity = std::numeric_limits<double>::infinity();
	if (_double == _double && _double != infinity && _double != -infinity &&
		(_double > std::numeric_limits<float>::max() ||
		_double < -std::numeric_limits<float>::max()))
		return (IMPOSSIBLE);
	_float = static_cast<float>(_double);
	if (is_float)
		_double = static_cast<double>(_float);
	return (SUCCESS);
}

int	ScalarConverter::StrToInt()
{
	if (_double != _double ||
		_double <= static_cast<double>(std::numeric_limits<int>::min()) - 1.0 ||
		_double >= static_cast<double>(std::numeric_limits<int>::max()) + 1.0)
		return (IMPOSSIBLE);
	_int = static_cast<int>(_double);
	return (SUCCESS);
}

int	ScalarConverter::StrToChar()
{
	if (_int < 0 || _int > 127)
		return (IMPOSSIBLE);
	if (_int < 32 || _int == 127)
		return (NON_DISPLAYABLE);
	_char = static_cast<char>(_int);
	return (SUCCESS);
}

void	ScalarConverter::output(int char_status, int int_status,
		int float_status, int double_status)
{
	std::cout << "char: ";
	if (char_status == SUCCESS)
		std::cout << "'" << _char << "'";
	else if (char_status == NON_DISPLAYABLE)
		std::cout << "Non displayable";
	else
		std::cout << "impossible";

	std::cout << std::endl << "int: ";
	if (int_status == SUCCESS)
		std::cout << _int;
	else
		std::cout << "impossible";

	std::cout << std::endl << "float: ";
	if (float_status == SUCCESS)
		std::cout << formatNumber(_float) << "f";
	else
		std::cout << "impossible";

	std::cout << std::endl << "double: ";
	if (double_status == SUCCESS)
		std::cout << formatNumber(_double);
	else
		std::cout << "impossible";
	std::cout << std::endl;
}

void ScalarConverter::convert(const std::string& given_str)
{
	bool quoted_char = given_str.size() == 3 &&
		given_str[0] == '\'' && given_str[2] == '\'';
	bool plain_char = given_str.size() == 1 &&
		(given_str[0] < '0' || given_str[0] > '9');
	bool is_float = !given_str.empty() &&
		given_str[given_str.size() - 1] == 'f';
	int double_status;

	if (quoted_char || plain_char)
	{
		_double = static_cast<unsigned char>(given_str[quoted_char ? 1 : 0]);
		double_status = SUCCESS;
		is_float = false;
	}
	else
		double_status = StrToDouble(given_str);

	// if (double_status == SUCCESS)
	// {
	// 	int float_status = StrToFloat(is_float);
	// 	int int_status = StrToInt();
	// 	if (int_status == SUCCESS)
	// 		int char_status = StrToChar();
	// 	else
	// 		int char_status = IMPOSSIBLE;
	// }
	// else
	// {
	// 	int float_status = IMPOSSIBLE;
	// 	int int_status = IMPOSSIBLE;
	// }

	int float_status = double_status == SUCCESS ? StrToFloat(is_float) : IMPOSSIBLE;
	int int_status = double_status == SUCCESS ? StrToInt() : IMPOSSIBLE;
	int char_status = int_status == SUCCESS ? StrToChar() : IMPOSSIBLE;

	output(char_status, int_status, float_status, double_status);
}
