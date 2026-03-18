/*
    Name: [Muhammad Shayan]
    Student ID: [1384496]
    Due Date: March 6th, at 11:59pm
    Course: CIS*2500

    By including this statement in this header comment, 
    I certify that I have read and understood the University policy on academic integrity.

    I assert that this work is 100% my own. 
    
    I have appropriately acknowledged all material 
    (code, data, images, ideas or words) that I have used, 
    whether directly quoted or paraphrased.
    
    Furthermore, I certify that this assignment was prepared by me specifically for the CIS*2500 Winter 2026 course.
*/
#include "a3.h"
#include <string.h>



/* ── counting helper ── */

/*
 * Purpose:   Counts the total number of comma-separated float values
 *            across all lines in a CSV file.
 * Parameters:
 *   filename - path to the CSV file
 * Example:   countElements("data.csv"); // returns 1000
 * Effect:    Opens and reads the file; exits if file cannot be opened.
 * Return:    Total number of float values in the file
 */
static int countElements(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) { fprintf(stderr, "Cannot open %s\n", filename); exit(1); }
    int count = 0;
    char line[65536];
    while (fgets(line, sizeof(line), fp)) {
        char *tok = strtok(line, ",\n\r");
        while (tok) { count++; tok = strtok(NULL, ",\n\r"); }
    }
    fclose(fp);
    return count;
}

/* ══════════════════════════════════════════════
   PART 1 — Benchmarking
   ══════════════════════════════════════════════ */

/*
 * Purpose:   Benchmarks all six sorting algorithms (bubble, selection,
 *            insertion, merge, quick, hybrid merge) using clock() and
 *            prints the elapsed time for each in seconds.
 * Parameters:
 *   base - original unsorted array loaded from the CSV
 *   n    - number of elements in the array
 * Example:   benchmarkSorts(base, 1000);
 *            // prints execution time for each sort algorithm
 * Effect:    Copies base into a temporary array before each sort so the
 *            original data is preserved. Prints results to stdout.
 * Return:    void
 */
static void benchmarkSorts(float base[], int n) {
    float arr[MAX_ARRAY_SIZE];
    clock_t start, end;
    double elapsed;

    printf("=== PART 1: Benchmark Results ===\n\n");

    memcpy(arr, base, n * sizeof(float));
    start = clock();
    bubbleSort(arr, n);
    end = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Bubble Sort:       %.6f seconds\n", elapsed);

    memcpy(arr, base, n * sizeof(float));
    start = clock();
    selectionSort(arr, n);
    end = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Selection Sort:    %.6f seconds\n", elapsed);

    memcpy(arr, base, n * sizeof(float));
    start = clock();
    insertionSort(arr, n);
    end = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Insertion Sort:    %.6f seconds\n", elapsed);

    memcpy(arr, base, n * sizeof(float));
    start = clock();
    mergeSort(arr, n);
    end = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Merge Sort:        %.6f seconds\n", elapsed);

    memcpy(arr, base, n * sizeof(float));
    start = clock();
    quickSort(arr, n);
    end = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Quick Sort:        %.6f seconds\n", elapsed);

    memcpy(arr, base, n * sizeof(float));
    start = clock();
    hybridMergeSort(arr, 0, n - 1);
    end = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Hybrid Merge Sort: %.6f seconds\n", elapsed);

    printf("\n");
}

/* ══════════════════════════════════════════════
   PART 2 — Sorting Variants Demo
   ══════════════════════════════════════════════ */

/*
 * Purpose:   Demonstrates all six sorting variant functions by running
 *            each on a copy of the base array and printing before/after
 *            results to verify correct behaviour.
 * Parameters:
 *   base - original unsorted array loaded from the CSV
 *   n    - number of elements in the array
 * Example:   demoPart2(base, 1000);
 *            // prints before/after output for each sorting variant
 * Effect:    Copies base into a temporary array before each demo.
 *            Prints results to stdout. Does not modify base.
 * Return:    void
 */
static void demoPart2(float base[], int n) {
    float arr[MAX_ARRAY_SIZE];
    printf("=== PART 2: Sorting Variants Demo ===\n\n");

    memcpy(arr, base, n * sizeof(float));
    printf("selectionSortRange (indices 2 to 6):\n");
    printf("  Before: ");
    for (int i = 0; i < 10; i++) printf("%.2f ", arr[i]);
    printf("\n");
    selectionSortRange(arr, 2, 6, n);
    printf("  After:  ");
    for (int i = 0; i < 10; i++) printf("%.2f ", arr[i]);
    printf("\n\n");

    memcpy(arr, base, n * sizeof(float));
    printf("insertionSortFrom (startIndex = 5):\n");
    printf("  Before: ");
    for (int i = 0; i < 10; i++) printf("%.2f ", arr[i]);
    printf("\n");
    insertionSortFrom(arr, n, 5);
    printf("  After:  ");
    for (int i = 0; i < 10; i++) printf("%.2f ", arr[i]);
    printf("\n\n");

    memcpy(arr, base, n * sizeof(float));
    printf("bubbleSortFrontAndRear (front=5, rear=5):\n");
    printf("  Before front: ");
    for (int i = 0; i < 5; i++) printf("%.2f ", arr[i]);
    printf("  Before rear: ");
    for (int i = n - 5; i < n; i++) printf("%.2f ", arr[i]);
    printf("\n");
    bubbleSortFrontAndRear(arr, 5, 5, n);
    printf("  After front:  ");
    for (int i = 0; i < 5; i++) printf("%.2f ", arr[i]);
    printf("  After rear:  ");
    for (int i = n - 5; i < n; i++) printf("%.2f ", arr[i]);
    printf("\n\n");

    memcpy(arr, base, n * sizeof(float));
    printf("mergeSortFirstHalf:\n");
    printf("  First half before: ");
    for (int i = 0; i < 8; i++) printf("%.2f ", arr[i]);
    printf("\n");
    mergeSortFirstHalf(arr, n);
    printf("  First half after:  ");
    for (int i = 0; i < 8; i++) printf("%.2f ", arr[i]);
    printf("\n\n");

    memcpy(arr, base, n * sizeof(float));
    printf("hybridMergeSort (THRESHOLD=%d):\n", THRESHOLD);
    hybridMergeSort(arr, 0, n - 1);
    printf("  First 10 sorted: ");
    for (int i = 0; i < 10; i++) printf("%.2f ", arr[i]);
    printf("\n\n");

    memcpy(arr, base, n * sizeof(float));
    printf("quickSortPivot (middle element pivot):\n");
    quickSortPivot(arr, 0, n - 1);
    printf("  First 10 sorted: ");
    for (int i = 0; i < 10; i++) printf("%.2f ", arr[i]);
    printf("\n\n");
}

/* ══════════════════════════════════════════════
   PART 3 — Searching Demo
   ══════════════════════════════════════════════ */

/*
 * Purpose:   Demonstrates all five searching functions by running each
 *            on the base array (sorted where required) and printing
 *            results to verify correct behaviour.
 * Parameters:
 *   base - original unsorted array loaded from the CSV
 *   n    - number of elements in the array
 * Example:   demoPart3(base, 1000);
 *            // prints search results for each algorithm
 * Effect:    Creates sorted copies of base as needed for binary/ternary
 *            search. Injects duplicates to test binarySearchFirst.
 *            Prints results to stdout. Does not modify base.
 * Return:    void
 */
static void demoPart3(float base[], int n) {
    float arr[MAX_ARRAY_SIZE];
    printf("=== PART 3: Searching Demo ===\n\n");

    float target = base[5];
    int idx = linearSearch(base, n, target);
    printf("linearSearch(%.4f): index = %d\n", target, idx);

    memcpy(arr, base, n * sizeof(float));
    arr[10] = arr[5];
    int indices[MAX_ARRAY_SIZE];
    int found = linearSearchAll(arr, n, arr[5], indices);
    printf("linearSearchAll(%.4f): %d match(es) at:", arr[5], found);
    for (int i = 0; i < found; i++) printf(" %d", indices[i]);
    printf("\n");

    memcpy(arr, base, n * sizeof(float));
    mergeSort(arr, n);
    float bTarget = arr[n / 3];
    idx = binarySearch(arr, n, bTarget);
    printf("binarySearch(%.4f): index = %d\n", bTarget, idx);

    float dupVal = arr[n / 2];
    arr[n / 2 - 1] = dupVal;
    mergeSort(arr, n);
    idx = binarySearchFirst(arr, n, dupVal);
    printf("binarySearchFirst(%.4f): first duplicate index = %d\n", dupVal, idx);

    float nonDup = -99999.0f;
    for (int i = 1; i < n - 1; i++) {
        if (arr[i] != arr[i - 1] && arr[i] != arr[i + 1]) {
            nonDup = arr[i];
            break;
        }
    }
    idx = binarySearchFirst(arr, n, nonDup);
    printf("binarySearchFirst(%.4f) [non-duplicate]: index = %d (expect -1)\n", nonDup, idx);

    memcpy(arr, base, n * sizeof(float));
    mergeSort(arr, n);
    float tTarget = arr[n / 4];
    idx = ternarySearch(arr, 0, n - 1, tTarget);
    printf("ternarySearch(%.4f): index = %d\n", tTarget, idx);

    printf("\n");
}

/* ══════════════════════════════════════════════
   main
   ══════════════════════════════════════════════ */

/*
 * Purpose:   Entry point of the program. Loads the dataset from data.csv,
 *            then runs benchmarking (Part 1), sorting variant demos (Part 2),
 *            and searching demos (Part 3).
 * Parameters:
 *   void
 * Example:   Run ./a3_mshaya01 from the command line
 * Effect:    Loads data from data.csv into memory and prints results for
 *            all three parts to stdout.
 * Return:    0 on successful execution
 */
int main(void) {
    int n = countElements("data.csv");
    if (n > MAX_ARRAY_SIZE) n = MAX_ARRAY_SIZE;
    printf("Loaded %d elements from data.csv\n\n", n);

    float base[MAX_ARRAY_SIZE];
    loadArray("data.csv", base, n);

    benchmarkSorts(base, n);
    demoPart2(base, n);
    demoPart3(base, n);

    return 0;
}