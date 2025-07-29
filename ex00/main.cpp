#include "BitcoinExchange.hpp"
/*

#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
	if (ac == 2)
	{
		try
		{
			std::string db = "data.csv";
			BitcoinExchange exchange(db);
			std::string input_file = av[1];
			exchange.process_input(input_file);
		}
		catch (const std::exception &e)
		{
			std::cerr << "Exception: " << e.what() << std::endl;
			return 1;
		}
		return 0;
	}
	else
	{
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}
}
*/
int main(int ac , char **av)
{
	(void)av;
	(void)ac;
	if (ac == 3)
	{
		try
		{
			// get intputs and call the aproprite functions
			;
		}
		catch(...){}
		return (0);
	}
	else
	{
		std::cerr << "invalid input" << std::endl;
		return (1);
	}

}
