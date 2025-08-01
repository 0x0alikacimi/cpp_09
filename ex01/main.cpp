	#include "RPN.hpp"

bool is_op(char c)
{
	if (c == '+' || c == '-' || c == '/'|| c == '*')
		return (true);
	return (false);
}

bool is_valid_number(const std::string &str, int &num)
{
	if (str.length() != 1 || !isdigit(str[0]))
		return (false);
	num = str[0] - '0';
	return (true);
}

void c(std::string str)
{
	std::stack<int> ms;
	std::stringstream strm(str);
	std::string tok;
	int num;
	while (strm >> tok)
	{
		if (tok.empty() || (std::isdigit(tok[0]) && is_op(tok[0])) )
		{
			std::cerr << "Error" << std::endl;
			return ;
		}
		if (tok.size() == 1 && is_op(tok[0]))
		{
			std::cout << "Operator found: " << tok << std::endl;
		}
		else if(is_valid_number(tok, num))
		{
			std::cout << "Operator found: " << tok << std::endl;
		}
		else
			std::cerr << "Error" << std::endl;
	}
}

int main (int ac , char **av)
{
	if (ac == 2)
	{
		c(av[1]);
	}
	else
		std::cerr << "invalid args" << std::endl;
}
