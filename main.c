#include "a3.h"
#include <string.h>

#define DATA_FILE "data.csv"

/* ── helpers ─────────────────────────────────── */
/* ── counting helper: parse CSV to get element count ── */
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
static void benchmarkSorts(float base[], int n) {
    float arr[MAX_ARRAY_SIZE];
    clock_t start, end;
    double elapsed;

    printf("=== PART 1: Benchmark Results ===\n\n");

    /* Bubble Sort */
    memcpy(arr, base, n * sizeof(float));
    start = clock();
    bubbleSort(arr, n);
    end = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Bubble Sort:       %.6f seconds\n", elapsed);

    /* Selection Sort */
    memcpy(arr, base, n * sizeof(float));
    start = clock();
    selectionSort(arr, n);
    end = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Selection Sort:    %.6f seconds\n", elapsed);

    /* Insertion Sort */
    memcpy(arr, base, n * sizeof(float));
    start = clock();
    insertionSort(arr, n);
    end = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Insertion Sort:    %.6f seconds\n", elapsed);

    /* Merge Sort */
    memcpy(arr, base, n * sizeof(float));
    start = clock();
    mergeSort(arr, n);
    end = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Merge Sort:        %.6f seconds\n", elapsed);

    /* Quick Sort */
    memcpy(arr, base, n * sizeof(float));
    start = clock();
    quickSort(arr, n);
    end = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Quick Sort:        %.6f seconds\n", elapsed);

    /* Hybrid Merge Sort */
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
static void demoPart2(float base[], int n) {
    float arr[MAX_ARRAY_SIZE];
    printf("=== PART 2: Sorting Variants Demo ===\n\n");

    /* 1. selectionSortRange — sort indices 2..6 */
    memcpy(arr, base, n * sizeof(float));
    printf("selectionSortRange (indices 2 to 6):\n");
    printf("  Before: ");
    for (int i = 0; i < 10; i++) printf("%.2f ", arr[i]);
    printf("\n");
    selectionSortRange(arr, 2, 6, n);
    printf("  After:  ");
    for (int i = 0; i < 10; i++) printf("%.2f ", arr[i]);
    printf("\n\n");

    /* 2. insertionSortFrom — sort from index 5 onward */
    memcpy(arr, base, n * sizeof(float));
    printf("insertionSortFrom (startIndex = 5):\n");
    printf("  Before: ");
    for (int i = 0; i < 10; i++) printf("%.2f ", arr[i]);
    printf("\n");
    insertionSortFrom(arr, n, 5);
    printf("  After:  ");
    for (int i = 0; i < 10; i++) printf("%.2f ", arr[i]);
    printf("\n\n");

    /* 3. bubbleSortFrontAndRear — sort first 5 and last 5 */
    memcpy(arr, base, n * sizeof(float));
    printf("bubbleSortFrontAndRear (front=5, rear=5):\n");
    printf("  Before: ");
    for (int i = 0; i < 10; i++) printf("%.2f ", arr[i]);
    printf("...\n");
    bubbleSortFrontAndRear(arr, 5, 5, n);
    printf("  After front: ");
    for (int i = 0; i < 5; i++) printf("%.2f ", arr[i]);
    printf("  After rear:  ");
    for (int i = n - 5; i < n; i++) printf("%.2f ", arr[i]);
    printf("\n\n");

    /* 4. mergeSortFirstHalf */
    memcpy(arr, base, n * sizeof(float));
    printf("mergeSortFirstHalf:\n");
    printf("  First half before: ");
    for (int i = 0; i < n / 2 && i < 8; i++) printf("%.2f ", arr[i]);
    printf("\n");
    mergeSortFirstHalf(arr, n);
    printf("  First half after:  ");
    for (int i = 0; i < n / 2 && i < 8; i++) printf("%.2f ", arr[i]);
    printf("\n\n");

    /* 5. hybridMergeSort */
    memcpy(arr, base, n * sizeof(float));
    printf("hybridMergeSort (THRESHOLD=%d):\n", THRESHOLD);
    hybridMergeSort(arr, 0, n - 1);
    printf("  First 10 sorted: ");
    for (int i = 0; i < 10; i++) printf("%.2f ", arr[i]);
    printf("\n\n");

    /* 6. quickSortPivot (middle pivot) */
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
static void demoPart3(float base[], int n) {
    float arr[MAX_ARRAY_SIZE];
    printf("=== PART 3: Searching Demo ===\n\n");

    /* ── Linear Search ── */
    float target = base[5];   /* pick a known value */
    int idx = linearSearch(base, n, target);
    printf("linearSearch(%.4f): index = %d\n", target, idx);

    /* ── Linear Search All ── */
    /* Inject a duplicate to demonstrate */
    memcpy(arr, base, n * sizeof(float));
    arr[10] = arr[5];   /* create duplicate */
    int indices[MAX_ARRAY_SIZE];
    int found = linearSearchAll(arr, n, arr[5], indices);
    printf("linearSearchAll(%.4f): %d match(es) at index/indices:", arr[5], found);
    for (int i = 0; i < found; i++) printf(" %d", indices[i]);
    printf("\n");

    /* ── Binary Search (needs sorted array) ── */
    memcpy(arr, base, n * sizeof(float));
    mergeSort(arr, n);
    float bTarget = arr[n / 3];   /* pick a value known to exist */
    idx = binarySearch(arr, n, bTarget);
    printf("binarySearch(%.4f) on sorted array: index = %d  value = %.4f\n",
           bTarget, idx, idx >= 0 ? arr[idx] : -1.0f);

    /* ── Binary Search First (duplicate) ── */
    /* Inject duplicates into the sorted array */
    float dupVal = arr[n / 2];
    arr[n / 2 - 1] = dupVal;   /* place duplicate just before */
    /* Re-sort to keep it valid */
    mergeSort(arr, n);
    /* Find where dupVal sits now */
    idx = binarySearchFirst(arr, n, dupVal);
    printf("binarySearchFirst(%.4f): first duplicate index = %d\n", dupVal, idx);

    /* Test a non-duplicate value */
    float nonDup = -99999.0f;
    /* Find a value that appears exactly once */
    for (int i = 1; i < n - 1; i++) {
        if (arr[i] != arr[i - 1] && arr[i] != arr[i + 1]) {
            nonDup = arr[i];
            break;
        }
    }
    idx = binarySearchFirst(arr, n, nonDup);
    printf("binarySearchFirst(%.4f) [non-duplicate]: index = %d (expect -1)\n",
           nonDup, idx);

    /* ── Ternary Search ── */
    memcpy(arr, base, n * sizeof(float));
    mergeSort(arr, n);
    float tTarget = arr[n / 4];
    idx = ternarySearch(arr, 0, n - 1, tTarget);
    printf("ternarySearch(%.4f) on sorted array: index = %d  value = %.4f\n",
           tTarget, idx, idx >= 0 ? arr[idx] : -1.0f);

    printf("\n");
}

/* ══════════════════════════════════════════════
   main
   ══════════════════════════════════════════════ */
int main(void) {
    int n = countElements(DATA_FILE);
    if (n > MAX_ARRAY_SIZE) n = MAX_ARRAY_SIZE;
    printf("Loaded %d elements from %s\n\n", n, DATA_FILE);

    float base[MAX_ARRAY_SIZE];
    loadArray(DATA_FILE, base, n);

    benchmarkSorts(base, n);
    demoPart2(base, n);
    demoPart3(base, n);

    return 0;
}
