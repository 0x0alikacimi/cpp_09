#include "RPN.hpp"

void rpn_ccalculation(std::string &str);

int main (int ac , char **av)
{
	if (ac == 2)
	{
		std::string str = av[1];
		rpn_ccalculation(str);
	}
	else
		std::cerr << "invalid args" << std::endl;
}
