// #include "PmergeMe.hpp"
#include <utility>
#include <iostream>
#include <vector>
#include <iostream>
#include  <array>
using namespace std;

void merge(int arr[], int l, int m, int r) {
	int i, j, k;
	int n1 = m - l + 1;
	int n2 =  r - m;

	int L[n1], R[n2];

	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1+ j];

	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		} else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

void mergeSort(int arr[], int l, int r) {
	if (l < r) {
		int m = l+(r-l)/2;
		mergeSort(arr, l, m);
		mergeSort(arr, m+1, r);
		merge(arr, l, m, r);
	}
}

void printArray(std::vector<int> array) {
	std::vector<int>::iterator it = array.begin();
	for (;it != array.end(); it++){
		std::cout << *it << std::endl ;
	}
}
int main (int ac, char **av)
{
	std::vector<std::pair<int , int> > test ;
	int holder = -1;
	for (int index = 0; index < 10; index++){
		if (index % 2 == 0)
			test.push_back(std::make_pair(index ,index * 2 - 4 + 10));
			else
			test.push_back(std::make_pair(index * 2 - 4 + 10,index));
	}
	std::vector<std::pair<int , int> >::iterator it = test.begin();
	std::vector<int> largerElements ;
	for (;it != test.end(); it++){
		holder = it->first ;
		if (it->first < it->second){
			it->first = it->second ;
			it->second = holder ;
		}
		std::cout << " ====== >  " << it->first << " | " << it->second <<
		std::endl ;
		largerElements.push_back(it->first);
	}
}
