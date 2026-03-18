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
Yes. The O(n²) algorithms (Bubble Sort, Selection Sort, Insertion Sort) are all significantly slower than the O(n log n) algorithms (Merge Sort, Quick Sort, Hybrid Merge Sort). Within the O(n²) group, Bubble Sort is slowest and Insertion Sort is fastest, which matches theory since Insertion Sort makes fewer comparisons on partially ordered data. Within the O(n log n) group, all three are close, with Quick Sort edging out the others due to lower constant factors and better cache performance.

**Why is Merge Sort usually faster than Bubble Sort?**  
Merge Sort runs in O(n log n) time in all cases. It divides the array in half each recursion and merges in linear time, so total work grows as n log n. Bubble Sort runs in O(n²) because it repeatedly scans the full unsorted portion, making a comparison for nearly every pair of elements. For n = 1000, O(n log n) ≈ 10,000 operations versus O(n²) ≈ 1,000,000 operations — roughly 100x fewer, which matches the observed speedup.

---

## Part 3: Ternary Search

**How ternary search differs from binary search:**  
Binary search splits the array into two halves using one midpoint, discarding half the search space per step. Ternary search splits the array into three parts using two midpoints (mid1 and mid2), discarding one third of the search space per step.

**Time complexity:**  
Ternary search has a worst-case time complexity of O(log₃ n), compared to binary search's O(log₂ n).

**Is ternary search more or less efficient than binary search?**  
Despite the smaller logarithm base, ternary search is less efficient than binary search in terms of worst-case number of comparisons. Each step of ternary search requires up to 4 comparisons versus binary search's 2. Since 4 × log₃ n > 2 × log₂ n for all n > 1, binary search makes fewer total comparisons and is the preferred algorithm in practice.