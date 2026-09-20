#include "ScalarConverter.hpp"

char	ScalarConverter::_char;
int		ScalarConverter::_int;
float	ScalarConverter::_float;
double	ScalarConverter::_double;


/*  private  */


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
	(void)given_str;
	_double = 4.2;
	return (1);
}

int	ScalarConverter::StrToFloat(const std::string& given_str)
{
	(void)given_str;
	_float = 4.2f;
	return (1);
}

int	ScalarConverter::StrToInt(const std::string& given_str)
{
	(void)given_str;
	_int = 42;
	return (1);
}

int	ScalarConverter::StrToChar(const std::string& given_str)
{
	(void)given_str;
	_char = '4';
	return (1);
}

void	ScalarConverter::output()
{
	std::cout << "char: " << _char << std::endl;
	std::cout << "int: " << _int << std::endl;
	std::cout << "float: " << _float  << "f" << std::endl;		// impossibleとかの時に、fも出力してしまうかも注意
	std::cout << "double: " << _double << std::endl;
}


/*  public  */


void ScalarConverter::convert(const std::string& given_str)
{
	// char		_char;
	// int		_int;
	// float	_float;
	// double	_double;

	StrToDouble(given_str);
	StrToFloat(given_str);
	StrToInt(given_str);
	StrToChar(given_str);

	output();
}

