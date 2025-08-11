/*******************************************************************************************
**  EXPLANATION : Merge Sort (with mergeInsert_v) as implemented in PmergeMe

	GOAL :
		Sort a std::vector<std::pair<int,int>> by the `.first` value of each pair.

	HOW IT WORKS (high-level):
		1. Recursively split the vector into halves until each half has size <= 1.
		2. Merge the sorted halves back together in order, using `mergeInsert_v`.
		3. The recursion tree unwinds, producing bigger and bigger sorted sections,
		until we have one fully sorted vector.

	BASE CASE :
		Recursion stops when:   w.size() <= 1
		At that point, the function simply returns `w` (already "sorted").

	MERGE STEP :
		`mergeInsert_v(left, right)` takes two sorted vectors and produces one sorted
		vector by comparing elements from the start of each list and taking the smaller.

********************************************************************************************/


/********************************************************************************************
	 RECURSION TREE VISUALIZATION

	Example input: w = [(9,3), (7,5), (8,4), (6,2)]

	LEVEL 0:					mergeSort_v([(9,3), (7,5), (8,4), (6,2)])
								/										\
	LEVEL 1:			mergeSort_v([(9,3),(7,5)])					mergeSort_v([(8,4),(6,2)])
					/					\							/				\
	LEVEL 2:	 mergeSort_v([(9,3)])	mergeSort_v([(7,5)])	mergeSort_v([(8,4)])	mergeSort_v([(6,2)])

	BASE CASES (size <= 1): these return immediately:
	[(9,3)], [(7,5)], [(8,4)], [(6,2)]

	MERGING BACK UP :
	LEVEL 2 -> LEVEL 1:
	mergeInsert_v( [(9,3)], [(7,5)] )  => [(7,5), (9,3)]
	mergeInsert_v( [(8,4)], [(6,2)] )  => [(6,2), (8,4)]

	LEVEL 1 -> LEVEL 0:
	mergeInsert_v( [(7,5),(9,3)], [(6,2),(8,4)] )
		Compare 7 < 6? No  → take (6,2)
		Compare 7 < 8? Yes → take (7,5)
		Compare 9 < 8? No  → take (8,4)
		Append leftover (9,3)
	=> [(6,2), (7,5), (8,4), (9,3)]


	FINAL RESULT :
		Sorted vector of pairs by `.first`: [(6,2), (7,5), (8,4), (9,3)]
********************************************************************************************/


/********************************************************************************************
	 DETAILED MERGE FUNCTION WALKTHROUGH :

	std::vector<std::pair<int,int>> mergeInsert_v(left, right):

	Input:	left  = [(a1,b1), (a2,b2), ...]  (sorted by .first)
			right = [(c1,d1), (c2,d2), ...]  (sorted by .first)
	Output: res	= merged sorted vector

	Process:
		size_t i = 0, j = 0;

		// Compare first elements from left and right
		while (i < left.size() && j < right.size()) {
			if (left[i].first < right[j].first)
				res.push_back(left[i++]);	// take from left
			else
				res.push_back(right[j++]);	// take from right
		}

		// Append leftovers from whichever side is not empty
		while (i < left.size())
			res.push_back(left[i++]);
		while (j < right.size())
			res.push_back(right[j++]);

	Notes:
		- This works because both `left` and `right` are already sorted when mergeInsert_v is called.
		- At each step, we pick the smaller `.first` to keep the merged list sorted.
		- Complexity: O(n) for merge step, O(n log n) overall for merge sort.
********************************************************************************************/


/********************************************************************************************
	 WHY RECURSION STOPS :
	`if (w.size() <= 1) return w;`
	- This is the base case: a vector with 0 or 1 element is already sorted.
	- No further splitting or merging needed.
********************************************************************************************/
