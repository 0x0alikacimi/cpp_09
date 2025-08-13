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

BitcoinExchange::BitcoinExchange(std::string &data_base_file)
{
	std::ifstream file(data_base_file.c_str());
	std::string line, key, val;
	if (!file.is_open())
	{
		std::cerr << "problem while opening the db file " << std::endl;;exit(1);
	}
	std::getline(file, line);
	if (line != "date,exchange_rate")
	{
		std::cerr << "Error: invalid db header"<< std::endl;file.close();exit(1);
	}
	while (std::getline(file, line))
	{
		size_t pos = line.find(',');
		if (pos == std::string::npos)
		{
			std::cerr << line << " is invalid form " << std::endl;file.close();exit(1);
		}
		key  = line.substr(0, pos);
		val = line.substr(pos + 1);
		data[key] = atof(val.c_str());
	}
	file.close();
}

bool is_all_digit(std::string &str)
{
	size_t i = 0;
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
	int y, m, d;
	std::string year_str, month_str, day_str;
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
	{
		std::cerr << date << " invalid date structure" << std::endl;return (false);
	}
	year_str = date.substr(0, 4);
	month_str = date.substr(5, 2);
	day_str = date.substr(8, 2);
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

bool valid_amount(std::string str)
{
	int i = 0;
	if (str.empty())
	{
		std::cerr << "invalid amount "<< std::endl;
		return (false);
	}
	if (str[0] == '-')
	{
		if (str[1] && !std::isdigit(str[1]))
			std::cerr << "invalid amount "<< std::endl;
		else
			std::cerr << "Error: not a positive number." << std::endl;
		return (false);
	}
	if (!std::isdigit(str[0]))
	{
		std::cerr << "invalid amount "<< std::endl;
		return (false);
	}
	int flag = 0;
	while (str[i])
	{
		if (str[i] != '.' && !std::isdigit(str[i]))
		{
			std::cerr << "invalid amount "<< std::endl;
			return (false);
		}
		if (str[i] == '.')
		{
			if (flag == 0)
				flag = 1;
			else
			{
				std::cerr << "invalid amount "<< std::endl;
				return (false);
			}
		}
		if ((str[i] == '.' && !str[i + 1]) ||
		(str[i] == '.' && str[i + 1] && !std::isdigit(str[i + 1])))
		{
			std::cerr << "invalid amount "<< std::endl;
			return (false);
		}
		i++;
	}
	return (true);
}
void BitcoinExchange::exec_line(std::string &line)
{
	std::string key = line.substr(0, 10);
	std::string val = line.substr(13);
	char *end;
	double value = std::strtod(val.c_str(), &end);
	std::map<std::string, float>::iterator it;
	if (*end != '\0')
	{
		std::cerr << "Error: bad input => " << val << std::endl;return;
	}
	if (value > 1000)
	{
		std::cerr << "Error: too large a number." << std::endl;return;
	}
	it = data.find(key);
	if (it == data.end())
	{
		it = data.lower_bound(key);
		/*returns an iterator pointing to the first element
			that is not less than the key*/
		if (it == data.begin())
		{
			std::cerr << "Error: no earlier date for " << key << std::endl;
			return;
		}
		--it;
	}
	std::cout << key << " => " << value << " = "
		<< (value * it->second) << std::endl;
}

void BitcoinExchange::deal_with_line(std::string &line)
{
	std::string str;

	if (line .size() < 14)
	{
		std::cerr << line << " invalid input" << std::endl;
		return ;
	}
	str = line.substr(0, 10);
	if (!valid_date(str) || line[10] != ' ' || line[11] != '|' || line[12] != ' ')/****/
		return ;
	str = line.substr(13);
	if (!valid_amount(str))
	{
		return ;
	}
	exec_line(line);
}

void BitcoinExchange:: deal_with_input(std::string &input_file)
{
	std::ifstream file(input_file.c_str());
	std::string line;
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}
	std::getline(file, line);
	if (line != "date | value")
	{
		std::cerr << "Error: invalid input header" << std::endl;file.close();return;
	}
	while (std::getline(file, line))
	{
		deal_with_line(line);
	}
	file.close();
}

