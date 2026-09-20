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



int isDouble(const std::string& given_str)
{
	const char* str = given_str.c_str();
    char* endptr;

    std::strtod(str, &endptr);
	if (endptr == str)
		return (IMPOSSIBLE);
	else if (*endptr == '\0')
		return (SUCCESS);
	else if (*endptr == 'f' && *(endptr + 1) == '\0')
		return (SUCCESS);
	else
		return (IMPOSSIBLE);
}

int	ScalarConverter::StrToDouble(const std::string& given_str)
{
	int retnum = isDouble(given_str);
	char *endptr;
	_double = std::strtod(given_str.c_str(), &endptr);
	// std::cout << endptr << std::endl;
	if (endptr == "f")
		return (SUCCESS);
	if (*endptr != 0)
		return (IMPOSSIBLE);
	return (SUCCESS);
}

int	ScalarConverter::StrToFloat(const std::string& given_str)
{
	(void)given_str;
	_float = 4.2f;
	return (SUCCESS);
}

int	ScalarConverter::StrToInt(const std::string& given_str)
{
	(void)given_str;
	_int = 42;
	return (SUCCESS);
}

int	ScalarConverter::StrToChar(const std::string& given_str)
{
	(void)given_str;
	_char = '4';
	return (SUCCESS);
}

void	ScalarConverter::output()
{
	static std::string const kata[] = {

	}	;
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

