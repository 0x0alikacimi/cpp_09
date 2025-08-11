vector
	A sequence container that stores elements contiguously in memory (like a C array, but resizable)
	Direct/random access


	How it works internally:
		Allocates a single block of memory large enough for current size + some extra capacity.
		When it runs out of space, it allocates a bigger block, copies/moves existing elements, and frees the old block
		Elements are always in one continuous memory block.

deque
	A double-ended queue container — supports fast insertion/removal at both ends.
	Unlike vector, elements are not stored in one contiguous block.
	Instead, it’s implemented as a sequence of fixed-size blocks (segments) managed by a central map of pointers

	How it works internally:
		Memory is split into chunks (e.g., 512 or 1024 bytes depending on element size).
		The "map" holds pointers to these chunks
		When you push front or back, it may just allocate a new chunk rather than moving all elements.

		random access but requires two lookups:
			Find the right chunk in the map
			Find the element within that chunk
