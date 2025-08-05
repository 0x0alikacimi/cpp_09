#include "PmergeMe.hpp"

bool is_valid(std::string str)
{
	if (str.empty())
		return (false);
	int i = 0;
	while (str[i])
	{
		if (!std::isdigit(str[i]))
		{
			return (false);
		}
		i++;
	}
	return (true);
}

std::vector<int> get_data(int ac,char **av)
{
	std::vector<int> data;
	std::string arg;
	int i = 1;
	while (i < ac)
	{
		arg = av[i];
		if (!is_valid(arg))
		{
			std::cerr << "Error: Invalid input '" << arg << "'." << std::endl;
			exit(1);
		}
		else
			data.push_back(std::atoi(arg.c_str()));
		i++;
	}
	return (data);
}

void set_up(std::vector<int> &data)
{
	std::vector<int> vec(data.begin(), data.end());
	std::deque<int> deq(data.begin(), data.end());

	pmergeme_vec(vec);
	pmergeme_deq(deq);

	std::cout << "Final sorted vector:\n";
	for (size_t i = 0; i < vec.size(); ++i)
		std::cout << vec[i] << " ";
	std::cout << std::endl;

	std::cout << "Final sorted deque:\n";
	for (size_t i = 0; i < deq.size(); ++i)
		std::cout << deq[i] << " ";
	std::cout << std::endl;
}

int main(int ac , char **av)
{
	if (ac >= 3 && ac <= 3001)
	{
		std::vector<int> data = get_data(ac, av);
		set_up(data);
	}
	else
		std::cerr << "invalid number of args" << std::endl;
}
