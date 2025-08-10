/*
===============================================================
pmergeme_vec() — Step-by-Step Algorithm Walkthrough
===============================================================
This function sorts a vector<int> using a hybrid algorithm:
- Ford–Johnson (Merge-Insertion Sort) logic
- With Jacobsthal sequence–based insertion ordering
- Implemented with std::vector + std::lower_bound for efficiency

---------------------------------------------------------------
Step 1: Pair the elements
---------------------------------------------------------------
We iterate over `vec` in steps of 2 and create pairs (first, second):
Example: vec = [3, 8, 9, 1, 5, 2]
Pairs = [(3,8), (9,1), (5,2)]
If the number of elements is odd, the last one lets call it "straggler" and
will be inserted at the end.

---------------------------------------------------------------
Step 2: Ensure the first element is the bigger in each pair
---------------------------------------------------------------
We swap first/second in a pair if first < second.
Example before: [(3,8), (9,1), (5,2)]
Example after:  [(8,3), (9,1), (5,2)]

Why?
This lets us sort by the larger element first (main chain will start with them).

---------------------------------------------------------------
Step 3: Sort the pairs by their first element (merge sort)
---------------------------------------------------------------
We use mergeSort_v() → mergeInsert_v() to sort the vector of pairs.
Sorting is based on pair.first (the larger element).

Example before: [(8,3), (9,1), (5,2)]
Example after:  [(5,2), (8,3), (9,1)]   // sorted by first element

---------------------------------------------------------------
Step 4: Split into "main" and "pend"
---------------------------------------------------------------
split_pairs():
main = [first of each pair]
pend = [second of each pair]

Example:
main = [5, 8, 9]
pend = [2, 3, 1]

The "main" is already sorted.
The "pend" will be inserted into "main" in a specific order.

---------------------------------------------------------------
Step 5: Seed the main chain
---------------------------------------------------------------
We insert pend[0] at the beginning of main.
Example:
main = [2, 5, 8, 9]
pend = [2, 3, 1] → effectively [3, 1] now pending insertion.

---------------------------------------------------------------
Step 6: Generate Jacobsthal sequence
---------------------------------------------------------------
get_sequence(pend.size()) returns an order of indexes to insert pend.
Example for pend.size()=3: seq = [1, 3, 2]
This order minimizes comparisons when inserting.

---------------------------------------------------------------
Step 7: Insert pending elements into main using binary search
---------------------------------------------------------------
We iterate through `seq` (skipping the already-inserted first),
find the correct position in `main` using std::lower_bound,
and insert.

Example flow:
Insert pend[seq[1]-1] = pend[2] into main → main grows
Insert pend[seq[2]-1] = pend[1] into main → main fully sorted

---------------------------------------------------------------
Step 8: Handle the straggler (if vec.size() is odd)
---------------------------------------------------------------
If there’s an odd leftover element from Step 1, insert it now
into the correct position in main.

---------------------------------------------------------------
Step 9: Done — main is sorted
---------------------------------------------------------------
We replace vec with main and measure execution time.

---------------------------------------------------------------
Key Points for Evaluation:
---------------------------------------------------------------
- Complexity: Merge step O(n log n), insertion step O(n log n) via binary search.
- Containers: std::vector for contiguous storage (fast binary search),
  std::deque in pmergeme_deq() to compare performance.
- Algorithm choice: Ford–Johnson provides fewer comparisons than naive merge sort.
- Jacobsthal sequence ensures near-optimal insertion order.

===============================================================
*/
