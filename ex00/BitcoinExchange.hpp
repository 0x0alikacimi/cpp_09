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
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange &operator=(const BitcoinExchange &other);
		~BitcoinExchange();

		BitcoinExchange(std::string &filename);
		void deal_with_input(std::string &input_file);
		void exec_line(const std::string &line);

};

#endif
