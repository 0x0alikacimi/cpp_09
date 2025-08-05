#include "PmergeMe.hpp"

void ensure_first_is_bigger(std::deque<std::pair<int, int> > &pairs)
{
	int temp;
	size_t i = 0;
	while (i < pairs.size())
	{
		if (pairs[i].first < pairs[i].second)
		{
			temp = pairs[i].first;
			pairs[i].first = pairs[i].second;
			pairs[i].second = temp;
		}
		i++;
	}
}

void split_pairs(std::deque<std::pair<int, int> > &v_pairs, std::deque<int> &main, std::deque<int> &pend)
{
	main.clear();
	pend.clear();
	size_t i = 0;
	while (i < v_pairs.size())
	{
		main.push_back(v_pairs[i].first);
		pend.push_back(v_pairs[i].second);
		i++;
	}
}

void pmergeme_deq(std::deque<int> &vec)
{
	clock_t start = clock();
	std::deque<std::pair<int, int> > v_pairs;

	size_t i = 0;
	while (i + 1 < vec.size())
	{
		v_pairs.push_back(std::make_pair(vec[i], vec[i + 1]));
		i += 2;
	}

	if (i < vec.size())
	{
		std::cout << "Unpaired element left in the original deque: " << vec[i] << std::endl;
	}

	ensure_first_is_bigger(v_pairs);
	v_pairs = mergeSort_d(v_pairs);

	std::deque<int> main;
	std::deque<int> pend;
	split_pairs(v_pairs, main, pend);

	main.insert(main.begin(), pend[0]);
	std::vector<int> seq = get_sequence(pend.size());
	size_t j = 1;
	while (j < pend.size())
	{
		int idx = seq[j] - 1;
		std::deque<int>::iterator pos = std::lower_bound(main.begin(), main.end(), pend[idx]);
		main.insert(pos, pend[idx]);
		j++;
	}
	if (vec.size() % 2)
	{
		std::deque<int>::iterator pos = std::lower_bound(main.begin(), main.end(),vec[vec.size() - 1]);
		main.insert(pos, vec[vec.size() - 1]);
	}
	vec = main;
	clock_t end = clock();
	std::cout << "Time to process a range of " << vec.size() << " elements with std::deque: "
		<< (double)(end - start) / CLOCKS_PER_SEC * 1000000 << " us" << std::endl;
}
