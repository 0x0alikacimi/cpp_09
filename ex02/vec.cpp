#include "PmergeMe.hpp"

void ensure_first_is_bigger(std::vector<std::pair<int, int> > &pairs)
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

void split_pairs(std::vector<std::pair<int, int> > &v_pairs, std::vector<int> &main, std::vector<int> &pend)
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

void pmergeme_vec(std::vector<int> &vec)
{
	clock_t start = clock();
	std::vector<std::pair<int, int> > v_pairs;

	size_t i = 0;
	while (i + 1 < vec.size())
	{
		v_pairs.push_back(std::make_pair(vec[i], vec[i + 1]));
		i += 2;
	}

	ensure_first_is_bigger(v_pairs);
	v_pairs = mergeSort_v(v_pairs);

	std::vector<int> main;
	std::vector<int> pend;
	split_pairs(v_pairs, main, pend);

	main.insert(main.begin(), pend[0]);
	std::vector<int> seq = get_sequence(pend.size());
	size_t j = 1;
	while (j < pend.size())
	{
		int idx = seq[j] - 1;
		std::vector<int>::iterator pos = std::lower_bound(main.begin(), main.end(), pend[idx]);
		main.insert(pos, pend[idx]);
		j++;
	}
	if (vec.size() % 2)
	{
		std::vector<int>::iterator pos = std::lower_bound(main.begin(), main.end(),vec[vec.size() - 1]);
		main.insert(pos, vec[vec.size() - 1]);
	}
	vec = main;
	clock_t end = clock();
	std::cout << "Time to process a range of " << vec.size() << " elements with std::vector: "
		<< (double)(end - start) / CLOCKS_PER_SEC * 1000000 << " us" << std::endl;
}
