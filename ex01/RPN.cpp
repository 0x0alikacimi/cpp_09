#include "RPN.hpp"

bool is_op(char c)
{
	if (c == '+' || c == '-' || c == '/'|| c == '*')
		return (true);
	return (false);
}

bool is_valid_number(std::string &str, int &num)
{
	if (str.length() != 1 || !isdigit(str[0]))
		return (false);
	num = str[0] - '0';
	return (true);
}

bool exec_op(std::stack<int> &ms, char op)
{
	if (ms.size() < 2)
		return (false);
	int b = ms.top(); ms.pop();
	int a = ms.top(); ms.pop();
	int res = 0;

	if (op == '+')
		res = a + b;
	else if (op == '-')
		res = a - b;
	else if (op == '*')
		res = a * b;
	else if (op == '/')
	{
		if (b == 0)
			return (false);
		res = a / b;
	}
	ms.push(res);return (true);
}

void rpn_ccalculation(std::string &str)
{
	int num;
	/* A LIFO (Last In, First Out) container
	only push/pop from the top */
	std::stack<int> ms;
	std::stringstream strm(str);
	std::string tok;

	while (strm >> tok)
	{
		if (tok.empty())
		{
			std::cerr << "Error" << std::endl;
			return;
		}
		if (tok.length() == 1 && is_op(tok[0]))
		{
			if (!exec_op(ms, tok[0]))
			{
				std::cerr << "Error" << std::endl;return;
			}
		}
		else if (is_valid_number(tok, num))
		{
			ms.push(num);
		}
		else
		{
			std::cerr << "Error" << std::endl;return;
		}
	}
	if (ms.size() != 1)
	{
		std::cerr << "Error" << std::endl;
		return;
	}
	std::cout << ms.top() << std::endl;
}
