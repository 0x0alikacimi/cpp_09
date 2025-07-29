#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

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

bool valid_date(std::string &date)
{
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return (false);

	std::string year_str = date.substr(0, 4);
	std::string month_str = date.substr(5, 2);
	std::string day_str = date.substr(8, 2);

	int y = std::atoi(year_str.c_str());
	int m = std::atoi(month_str.c_str());
	int d = std::atoi(day_str.c_str());

	if (y < 2009 || m < 1 || m > 12 || d < 1 || d > 31)
		return false;
	return (true);
}
/*w33333*/
/*
	std::ifstream file(input_file.c_str());
	std::string line, key, val;
	if (!file.is_open())
	{
		std::cerr << "pronlem while opening the file " << std::endl;exit(1);
	}
	while (std::getline(file, line))
	{
		size_t pos = line.find(',');
		if (pos == std::string::npos)
		{
			// malfirmed line
			continue;
		}
		key  = line.substr(0, pos);
		val = line.substr(pos + 1);
		// trim white sapces
		key.erase(0, key.find_first_not_of(" \t"));
		key.erase(key.find_last_not_of(" \t") + 1);
		val.erase(0, val.find_first_not_of(" \t"));
		val.erase(val.find_last_not_of(" \t") + 1);
		data[key] = atof(val.c_str());

		if (valid_date())
	}
	file.close();
*/



void BitcoinExchange::process_input(std::string &input_file)
{
	std::ifstream file(input_file.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}
	std::string line, key, val;
	// std::getline(file, line);//skip header
	while (std::getline(file, line))
	{
		size_t d_pos = line.find('|');
		if (d_pos == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		key  = line.substr(0, d_pos);
		val = line.substr(d_pos + 1);
		// trim white sapces
		key.erase(0, key.find_first_not_of(" \t"));
		key.erase(key.find_last_not_of(" \t") + 1);
		val.erase(0, val.find_first_not_of(" \t"));
		val.erase(val.find_last_not_of(" \t") + 1);

		if (!valid_date(key))
		{
			std::cerr << "Error: bad input : " << key << std::endl;
			continue;
		}
		// float bc_val;//check the val if its valid (contain somthing else than nubers ..), then put it in bc_val, then check the bounds
		// before lokking for it in the base and printing the apropriate msg
	}
}

BitcoinExchange::BitcoinExchange(std::string &data_base_file)
{
	std::ifstream file(data_base_file.c_str());
	std::string line, key, val;
	if (!file.is_open())
	{
		std::cerr << "pronlem while opening the file " << std::endl;exit(1);
	}
	// std::getline(file, line);// skip header
	while (std::getline(file, line))
	{
		size_t pos = line.find(',');
		if (pos == std::string::npos)
		{
			continue;
		}
		key  = line.substr(0, pos);
		val = line.substr(pos + 1);
		if (!valid_date(key))
		{
			std::cerr << "Error: bad date format in database : " << key << std::endl;
			continue;
		}
		data[key] = atof(val.c_str());
	}
	file.close();
}
