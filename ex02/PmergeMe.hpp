#ifndef PMERGEME_HPP
#define PMERGEME_HPP


#include <iostream>
#include <utility>
#include <iostream>
#include <vector>
#include  <array>
#include <deque>

/************************ vector ************************/

void pmergeme_vec(std::vector<int> &vec);
std::vector<std::pair<int, int> > mergeInsert_v(std::vector<std::pair<int, int> > left, std::vector<std::pair<int, int> > right);
std::vector<std::pair<int, int> > mergeSort_v(std::vector<std::pair<int, int> > &w);

/************************ deque ************************/

void pmergeme_deq(std::deque<int> &vec);
std::deque<std::pair<int, int> > mergeInsert_d(std::deque<std::pair<int, int> > left, std::deque<std::pair<int, int> > right);
std::deque<std::pair<int, int> > mergeSort_d(std::deque<std::pair<int, int> > &w);

/*******************************************************/

std::vector<int> get_sequence(int pend_size);

#endif
