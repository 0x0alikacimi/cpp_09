#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <iostream>
#include <fstream>

/*
	map
	A container that stores key-value pairs
	Keys are unique
*/
class BitcoinExchange
{
	private:
		std::map<std::string , float> data;

	public:
		BitcoinExchange();
		BitcoinExchange(std::string &data_base_file);
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange &operator=(const BitcoinExchange &other);
		~BitcoinExchange();

		void deal_with_input(std::string &input_file);
		void deal_with_line(std::string &line);
		void exec_line(std::string &line);

};

#endif
