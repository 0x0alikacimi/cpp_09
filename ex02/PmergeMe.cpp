#include "PmergeMe.hpp"

/********************************************************* vector *********************************************************/

/******************* Merge Insertion *******************/

std::vector<std::pair<int, int> > mergeInsert_v(std::vector<std::pair<int, int> > left, std::vector<std::pair<int, int> > right)
{
	std::vector<std::pair<int, int> > res;
	size_t i = 0, j = 0;
	while (i < left.size() && j < right.size()){
		if (left[i].first < right[j].first) res.push_back(left[i++]);
		else res.push_back(right[j++]);
	}
	while (i < left.size()) res.push_back(left[i++]);
	while (j < right.size()) res.push_back(right[j++]);
	return (res);
}

std::vector<std::pair<int, int> > mergeSort_v(std::vector<std::pair<int, int> > &w)
{
	if (w.size() <= 1) return (w);
	int mid = w.size() / 2;
	std::vector<std::pair<int, int> >left(w.begin(), w.begin() + mid);
	std::vector<std::pair<int, int> >right(w.begin() + mid, w.end());
	return (mergeInsert_v(mergeSort_v(left), mergeSort_v(right)));
}
/**************************************************************************************************************************/



/********************************************************* deque *********************************************************/

/******************* Merge Insertion *******************/
std::deque<std::pair<int, int> > mergeInsert_d(std::deque<std::pair<int, int> > left, std::deque<std::pair<int, int> > right)
{
	std::deque<std::pair<int, int> > res;
	size_t i = 0, j = 0;
	while (i < left.size() && j < right.size()){
		if (left[i].first < right[j].first) res.push_back(left[i++]);
		else res.push_back(right[j++]);
	}
	while (i < left.size()) res.push_back(left[i++]);
	while (j < right.size()) res.push_back(right[j++]);
	return (res);
}

std::deque<std::pair<int, int> > mergeSort_d(std::deque<std::pair<int, int> > &w)
{
	if (w.size() <= 1) return (w);
	int mid = w.size() / 2;
	std::deque<std::pair<int, int> >left(w.begin(), w.begin() + mid);
	std::deque<std::pair<int, int> >right(w.begin() + mid, w.end());
	return (mergeInsert_d(mergeSort_d(left), mergeSort_d(right)));
}

/**************************************************************************************************************************/



/*********** jacbsthal's sequence ***********/

std::vector<int> get_sequence(int pend_size)
{
	std::vector<int> js_seq;
	js_seq.push_back(0);
	js_seq.push_back(1);
	js_seq.push_back(1);
	int i = 3;
	while (js_seq[i - 1] <= pend_size)
	{
		js_seq.push_back(js_seq[i - 1] + 2 * js_seq[i - 2]);
		i++;
	}
	std::vector<int> seq;seq.push_back(1);
	size_t j = 3;
	int first ;
	int last ;
	while (j < js_seq.size())
	{
		first = js_seq[j - 1];
		last = js_seq[j];
		if (last <= pend_size)
			seq.push_back(last);
		while(last > first)
		{
			if (last <= pend_size)
				seq.push_back(last);
			last--;
		}
		j++;
	}
	return (seq);
}

/********************************************/
