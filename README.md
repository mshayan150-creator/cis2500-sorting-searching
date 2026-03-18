# CIS*2500 Assignment 3 — README

## Part 1: Empirical Analysis

### Execution Times (1000 elements from `data.csv`)

- Bubble Sort:       0.003080
- Selection Sort:    0.001930
- Insertion Sort:    0.001069
- Merge Sort:        0.000225
- Quick Sort:        0.000141
- Hybrid Merge Sort: 0.000155

---

### Questions

**Which algorithm was fastest?**  
Quick Sort was the fastest at 0.000141 seconds.

**Which algorithm was slowest?**  
Bubble Sort was the slowest at 0.003080 seconds.

**Do the results match theoretical complexity?**  
Yes. The family of n² algorithms, such as Bubble Sort, Selection Sort, and Insertion Sort, are known to be much slower than their counterparts in the family of n log n, such as Merge Sort, Quick Sort, and Hybrid Merge Sort. Of the former, Bubble Sort is the slowest, and Insertion Sort is the fastest, as expected, since it makes fewer comparisons on partially sorted data. Of the latter, the three are roughly equal in speed, with Quick Sort being slightly ahead because of smaller constants and cache efficiency.

**Why is Merge Sort usually faster than Bubble Sort?**  
This is because the time complexity of the Merge Sort algorithm is always O(n log n). It divides the array in half at each step and then merges the two halves in linear time. Bubble Sort, however, takes O(n²) time because it continues to scan the unsorted portion of the array and compares nearly every pair of elements. If n is 1000, the first algorithm takes about 10,000 operations, but the second takes as many as 1,000,000 operations, or 100 times as many operations as the first algorithm, which is consistent with the speedup factor observed.

---

## Part 3: Ternary Search

**How ternary search differs from binary search:**  
In binary search, the array is divided into two halves with one midpoint. In each step of binary search, half of the search space is eliminated. In ternary search, the array is divided into three sections with two midpoints (mid1 and mid2), and one third of the search space is eliminated in each step.

**Time complexity:**  
Ternary search has a worst-case time complexity of O(log₃ n), compared to binary search's O(log₂ n).

**Is ternary search more or less efficient than binary search?**  
Although ternary search has a smaller logarithm base, it actually does more work in the worst case. In each iteration of ternary search, there could be as many as four comparisons. In contrast, binary search has only two comparisons. However, since 4 * log base 3 of n is always greater than 2 * log base 2 of n for all n greater than 1, binary search is preferred.