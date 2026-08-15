# CIS*2500 Sorting & Searching Algorithms

A C-based implementation and empirical analysis of fundamental sorting and searching algorithms developed for CIS*2500.

## Overview

This project explores the implementation, behavior, and performance of several classic algorithms for sorting and searching arrays of floating-point values.

The project includes standard algorithms as well as modified and hybrid versions designed to explore different approaches to solving the same problem.

## Sorting Algorithms

### Standard Sorting
- Selection Sort
- Insertion Sort
- Bubble Sort
- Merge Sort
- Quick Sort

### Sorting Variants
- Selection Sort on a specified range
- Insertion Sort from a specified index
- Bubble Sort on the front and rear portions of an array
- Merge Sort on the first half of an array
- Hybrid Merge-Insertion Sort
- Quick Sort using a middle-element pivot

## Searching Algorithms

- Linear Search
- Linear Search for all occurrences
- Binary Search
- Binary Search for the first occurrence of a duplicate
- Recursive Ternary Search

## Performance Analysis

The project measures sorting execution times using C's `clock()` function.

### Example Results

| Algorithm | Execution Time (1000 elements) |
|---|---:|
| Bubble Sort | 0.003080 s |
| Selection Sort | 0.001930 s |
| Insertion Sort | 0.001069 s |
| Merge Sort | 0.000225 s |
| Quick Sort | 0.000141 s |
| Hybrid Merge Sort | 0.000155 s |

In this test, **Quick Sort was the fastest**, while **Bubble Sort was the slowest**.

The results are consistent with the expected theoretical complexity of the algorithms. The quadratic-time algorithms—Bubble, Selection, and Insertion Sort—generally performed worse than the `O(n log n)` Merge, Quick, and Hybrid Merge Sort implementations.

## Complexity

| Algorithm | Average Time | Worst Case |
|---|---:|---:|
| Selection Sort | O(n²) | O(n²) |
| Insertion Sort | O(n²) | O(n²) |
| Bubble Sort | O(n²) | O(n²) |
| Merge Sort | O(n log n) | O(n log n) |
| Quick Sort | O(n log n) | O(n²) |
| Binary Search | O(log n) | O(log n) |
| Ternary Search | O(log₃ n) | O(log₃ n) |
| Linear Search | O(n) | O(n) |

## Ternary Search vs. Binary Search

Both algorithms reduce the search space logarithmically, but they divide the array differently.

**Binary Search** divides the search space into two sections using one midpoint.

**Ternary Search** divides the search space into three sections using two midpoints.

Although ternary search has a smaller logarithm base, each iteration requires additional comparisons. As a result, binary search is generally preferred for searching a sorted array.

## Project Structure

```text
├── a3.h
├── main.c
├── sorting.c
├── searching.c
├── a3_main.c
├── data.csv
├── Makefile
├── README.md
└── .gitlab-ci.yml
