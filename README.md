# selection
Implementation of a deterministically linear-time Selection algorithm. Without modification, the Selection algorithm's worst case time complexity is actually quadratic for the same reasons Quicksort is. By calculating the median-of-medians (a linear-time operation) instead of random choice for each successive pivot, we can guarantee that the Selection algorithm's runtime will grow linearly. Keep in mind that even though calculating the median-of-medians of the set is linear and random choice is constant, both operations will ultimately need to partition around the selected index, which is also asymptotically linear, so the overarching time complexity is not affected.

Check out this link for overview of the Selection algorithm: http://web.mit.edu/neboat/www/6.046-fa09/rec3.pdf
