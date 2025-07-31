#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
	this->data = other.data;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
	{
		this->data = other.data;
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
}

bool is_all_digit(std::string &str)
{
	int i = 0;
	while (i < str.size())
	{
		if (!std::isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool valid_date(std::string &date)
{
	int	y;
	int	m;
	int	d;
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
	{
		std::cerr << date << " invalid date structure" << std::endl;return (false);
	}
	std::string year_str = date.substr(0, 4);
	std::string month_str = date.substr(5, 2);
	std::string day_str = date.substr(8, 2);

	if (!is_all_digit(year_str) ||!is_all_digit(month_str) || !is_all_digit(day_str))
	{
		std::cerr << date << " invalid date " << std::endl;return (false);
	}

	y = std::atoi(year_str.c_str());
	m = std::atoi(month_str.c_str());
	d = std::atoi(day_str.c_str());

	if (y < 2009 || m < 1 || m > 12 || d < 1 || d > 31)
	{
		std::cerr << date << " invalid date range" << std::endl;return (false);
	}
	return (true);
}

bool valid_amount(std::string &amount)
{
	int i = 0;
	int flag = 0;
	if (amount.size() == 1 && !std::isdigit(amount[0]))
		return (false);
	else if (amount.size() > 1 && amount[0] == '-' && std::isdigit(amount[1]))
		return (false);
	while (i < amount.size())
	{
		if (amount[i] == '.')
			flag += 1;
		if (!std::isdigit(amount[i]) && amount[i] != '.')
			return (false);
		if (amount[i] == '.' && amount[i + 1] && std::isdigit(amount[i + 1]))
			return (false);
		i++;
	}
	return (true);
}

void BitcoinExchange::process_input(std::string &input_file)
{
	std::ifstream file(input_file.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}
	char* end;
	double value;
	std::map<std::string, float>::iterator it;
	std::string line, key, val;

	std::getline(file, line);
	if (line != "date | value")
	{
			std::cerr << "Error: invalid input header" << std::endl;return;
	}

	while (std::getline(file, line))
	{
		size_t d_pos = line.find('|');
		if (d_pos == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;continue;
		}

		key  = line.substr(0, d_pos);
		val = line.substr(d_pos + 1);

		key.erase(0, key.find_first_not_of(" \t"));
		key.erase(key.find_last_not_of(" \t") + 1);
		val.erase(0, val.find_first_not_of(" \t"));
		val.erase(val.find_last_not_of(" \t") + 1);

		if (!valid_date(key))
		{
			std::cerr << "Error: bad input => " << key << std::endl;
			continue;
		}
		value = std::strtod(val.c_str(), &end);
		if (*end != '\0')
		{
				std::cerr << "Error: bad input => " << val << std::endl;continue;
		}
		if (value < 0)
		{
				std::cerr << "Error: not a positive number." << std::endl;continue;
		}
		if (value > 1000)
		{
				std::cerr << "Error: too large a number." << std::endl;continue;
		}
		std::map<std::string, float>::iterator it = data.find(key);
		if (it == data.end())
		{
				it = data.lower_bound(key);
				if (it == data.begin())
				{
						std::cerr << "Error: no earlier for " << key << std::endl;continue;
				}
				--it;
		}
		std::cout << key << " => " << value << " = " << (value * it->second) << std::endl;
	}
}

bool valid_db_line(std::string &line)
{
	int i = 0;
	if (line.size() < 11)
		return (false);
	while (line[i])
	{
		if ((i == 4 || i == 7) && line[i] != '-')
			return (false);
		else if (i == 10 && line[i] != ',')
			return (false);
		else if (!std::isdigit(line[i]) && line[i] != '.')
			return (false);
		i++;
	}
	return (true);
}

BitcoinExchange::BitcoinExchange(std::string &data_base_file)
{
	std::ifstream file(data_base_file.c_str());
	std::string line, key, val;
	if (!file.is_open())
	{
		std::cerr << "pronlem while opening the db file " << std::endl;;exit(1);
	}
	std::getline(file, line);
	if (line != "date,exchange_rate")
	{
		std::cerr << "Error: invalid db header"<< std::endl;file.close();exit(1);
	}
	while (std::getline(file, line))
	{

		size_t pos = line.find(',');
		if (pos == std::string::npos || !valid_db_line(line))
		{
			std::cerr << line << "is invalid form " << std::endl;file.close();exit(1);
		}
		key  = line.substr(0, pos);
		val = line.substr(pos + 1);
		if (!valid_date(key))
			file.close();exit(1);
		if (!valid_amount(val))
		{
			std::cerr << line << " invalid amount" << std::endl;file.close();exit(1);
		}
		data[key] = atof(val.c_str());
	}
	file.close();
}

bool deal_with_line(std::string &line)
{
	int i = 0;
	std::string str;

	if (line.size() < 14)
	{
		std::cerr << line << "invalid input" << std::endl;
		return (false);
	}
	str = line.substr(0, 10);
	if (!valid_date(str) || line[10] != ' ' || line[11] != '|' || line[12] != ' ')
	{
		std::cerr << line << "invalid input" << std::endl;
		return (false);
	}
	str = line.substr(13, line.size() -1);
	if (valid_amount(str))
	{
		if (str.size() < 1 && isdigit(str[1]) && str[0] == '-')
			std::cerr <<  "Error: not a positive number." << std::endl;//khas nbyn chno li not a posi..
		return (false);
	}
	return (true);
}

void deal_with_input(std::string &input_file)
{
	std::ifstream file(input_file.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}
	std::string line, key, val;

	std::getline(file, line);
	if (line != "date | value")
	{
		std::cerr << "Error: invalid input header" << std::endl;file.close();return;
	}

	while (std::getline(file, line))
	{
		if (!deal_with_line(line))
			return;
		// else
			// execlin(line);
	}
}
