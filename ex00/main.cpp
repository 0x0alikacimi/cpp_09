#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
	if (ac == 2)
	{
		std::string input_file = av[1];
		std::string db_file = "data.csv";

		BitcoinExchange exchange(db_file);
		exchange.deal_with_input(input_file);

	}
	else
	{
		std::cerr << "invalid input" << std::endl;
		return (1);
	}
}
