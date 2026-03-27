#include "a3.h"
#include <string.h>

/* ─────────────────────────────────────────────
   PART 1 — Standard Sorting Algorithms
   ───────────────────────────────────────────── */

/*
 * Purpose:   Sorts an array of floats in ascending order using the
 *            selection sort algorithm.
 * Parameters:
 *   arr  - array of floats to be sorted
 *   size - number of elements in the array
 * Example:   float arr[] = {3.1, 1.2, 2.5};
 *            selectionSort(arr, 3);
 *            // arr is now {1.2, 2.5, 3.1}
 * Effect:    Modifies arr in-place so elements are in ascending order.
 * Return:    void
 */
void selectionSort(float arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIdx])
                minIdx = j;
        }
        if (minIdx != i) {
            float tmp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = tmp;
        }
    }
}

/*
 * Purpose:   Sorts an array of floats in ascending order using the
 *            insertion sort algorithm.
 * Parameters:
 *   arr  - array of floats to be sorted
 *   size - number of elements in the array
 * Example:   float arr[] = {3.1, 1.2, 2.5};
 *            insertionSort(arr, 3);
 *            // arr is now {1.2, 2.5, 3.1}
 * Effect:    Modifies arr in-place so elements are in ascending order.
 * Return:    void
 */
void insertionSort(float arr[], int size) {
    for (int i = 1; i < size; i++) {
        float key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

/*
 * Purpose:   Sorts an array of floats in ascending order using the
 *            bubble sort algorithm.
 * Parameters:
 *   arr  - array of floats to be sorted
 *   size - number of elements in the array
 * Example:   float arr[] = {3.1, 1.2, 2.5};
 *            bubbleSort(arr, 3);
 *            // arr is now {1.2, 2.5, 3.1}
 * Effect:    Modifies arr in-place so elements are in ascending order.
 *            Exits early if no swaps occur in a pass.
 * Return:    void
 */
void bubbleSort(float arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                float tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
}

/* ── Merge Sort helpers ── */

/*
 * Purpose:   Merges two sorted subarrays arr[left..mid] and
 *            arr[mid+1..right] into a single sorted subarray.
 * Parameters:
 *   arr   - array containing both subarrays
 *   left  - starting index of the left subarray
 *   mid   - ending index of the left subarray
 *   right - ending index of the right subarray
 * Example:   arr = {1.0, 3.0, 2.0, 4.0}, left=0, mid=1, right=3
 *            merge(arr, 0, 1, 3);
 *            // arr is now {1.0, 2.0, 3.0, 4.0}
 * Effect:    Modifies arr in-place by merging the two sorted halves.
 *            Allocates and frees temporary arrays internally.
 * Return:    void
 */
static void merge(float arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    float *L = (float *)malloc(n1 * sizeof(float));
    float *R = (float *)malloc(n2 * sizeof(float));

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else               arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

/*
 * Purpose:   Recursively divides and sorts the subarray arr[left..right]
 *            using the merge sort algorithm.
 * Parameters:
 *   arr   - array of floats to sort
 *   left  - starting index of the subarray
 *   right - ending index of the subarray
 * Example:   mergeSortHelper(arr, 0, 4);
 *            // sorts arr[0..4] in ascending order
 * Effect:    Modifies arr in-place by recursively sorting and merging.
 * Return:    void
 */
static void mergeSortHelper(float arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortHelper(arr, left, mid);
        mergeSortHelper(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

/*
 * Purpose:   Sorts an array of floats in ascending order using the
 *            merge sort algorithm with O(n log n) time complexity.
 * Parameters:
 *   arr  - array of floats to be sorted
 *   size - number of elements in the array
 * Example:   float arr[] = {3.1, 1.2, 2.5};
 *            mergeSort(arr, 3);
 *            // arr is now {1.2, 2.5, 3.1}
 * Effect:    Modifies arr in-place so elements are in ascending order.
 * Return:    void
 */
void mergeSort(float arr[], int size) {
    mergeSortHelper(arr, 0, size - 1);
}

/* ── Quick Sort helpers ── */

/*
 * Purpose:   Partitions the subarray arr[left..right] around a pivot
 *            (the last element), placing smaller elements to the left
 *            and larger elements to the right.
 * Parameters:
 *   arr   - array of floats to partition
 *   left  - starting index of the subarray
 *   right - ending index of the subarray (pivot element)
 * Example:   arr = {3.1, 1.2, 2.5}, partition(arr, 0, 2)
 *            // pivot = 2.5, returns index 1
 * Effect:    Rearranges elements in arr around the pivot in-place.
 * Return:    Index of the pivot after partitioning
 */
static int partition(float arr[], int left, int right) {
    float pivot = arr[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            i++;
            float tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
        }
    }
    float tmp = arr[i + 1]; arr[i + 1] = arr[right]; arr[right] = tmp;
    return i + 1;
}

/*
 * Purpose:   Recursively sorts the subarray arr[left..right] using
 *            the quicksort algorithm with last element as pivot.
 * Parameters:
 *   arr   - array of floats to sort
 *   left  - starting index of the subarray
 *   right - ending index of the subarray
 * Example:   quickSortHelper(arr, 0, 4);
 *            // sorts arr[0..4] in ascending order
 * Effect:    Modifies arr in-place by recursively partitioning and sorting.
 * Return:    void
 */
static void quickSortHelper(float arr[], int left, int right) {
    if (left < right) {
        int pi = partition(arr, left, right);
        quickSortHelper(arr, left, pi - 1);
        quickSortHelper(arr, pi + 1, right);
    }
}

/*
 * Purpose:   Sorts an array of floats in ascending order using the
 *            quicksort algorithm with O(n log n) average time complexity.
 * Parameters:
 *   arr  - array of floats to be sorted
 *   size - number of elements in the array
 * Example:   float arr[] = {3.1, 1.2, 2.5};
 *            quickSort(arr, 3);
 *            // arr is now {1.2, 2.5, 3.1}
 * Effect:    Modifies arr in-place so elements are in ascending order.
 * Return:    void
 */
void quickSort(float arr[], int size) {
    quickSortHelper(arr, 0, size - 1);
}

/* ─────────────────────────────────────────────
   PART 2 — Sorting Variants
   ───────────────────────────────────────────── */

/*
 * Purpose:   Sorts only the subarray between indices start and end
 *            (inclusive) using selection sort, leaving the rest unchanged.
 * Parameters:
 *   arr   - array of floats
 *   start - starting index of the range to sort
 *   end   - ending index of the range to sort
 *   size  - total number of elements in the array
 * Example:   float arr[] = {5.0, 3.0, 1.0, 4.0, 2.0};
 *            selectionSortRange(arr, 1, 3, 5);
 *            // arr is now {5.0, 1.0, 3.0, 4.0, 2.0}
 * Effect:    Modifies arr[start..end] in-place in ascending order.
 *            Elements outside [start, end] are unchanged.
 * Return:    void
 */
void selectionSortRange(float arr[], int start, int end, int size) {
    if (start < 0 || end >= size || start >= end) return;
    for (int i = start; i < end; i++) {
        int minIdx = i;
        for (int j = i + 1; j <= end; j++) {
            if (arr[j] < arr[minIdx])
                minIdx = j;
        }
        if (minIdx != i) {
            float tmp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = tmp;
        }
    }
}

/*
 * Purpose:   Sorts the array from startIndex to the end using insertion
 *            sort, leaving elements before startIndex unchanged.
 * Parameters:
 *   arr        - array of floats
 *   size       - total number of elements in the array
 *   startIndex - index from which sorting begins
 * Example:   float arr[] = {5.0, 3.0, 1.0, 4.0, 2.0};
 *            insertionSortFrom(arr, 5, 2);
 *            // arr is now {5.0, 3.0, 1.0, 2.0, 4.0}
 * Effect:    Modifies arr[startIndex..size-1] in-place in ascending order.
 *            Elements before startIndex are unchanged.
 * Return:    void
 */
void insertionSortFrom(float arr[], int size, int startIndex) {
    if (startIndex <= 0) startIndex = 1;
    for (int i = startIndex + 1; i < size; i++) {
        float key = arr[i];
        int j = i - 1;
        while (j >= startIndex && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

/*
 * Purpose:   Sorts the first `front` elements and the last `rear` elements
 *            of the array using bubble sort, leaving the middle unchanged.
 * Parameters:
 *   arr   - array of floats
 *   front - number of elements from the start to sort
 *   rear  - number of elements from the end to sort
 *   size  - total number of elements in the array
 * Example:   float arr[] = {5.0, 3.0, 9.0, 8.0, 1.0, 4.0, 2.0};
 *            bubbleSortFrontAndRear(arr, 2, 2, 7);
 *            // front 2 sorted, rear 2 sorted, middle unchanged
 * Effect:    Modifies the first `front` and last `rear` elements in-place.
 *            The middle portion arr[front..size-rear-1] is unchanged.
 * Return:    void
 */
void bubbleSortFrontAndRear(float arr[], int front, int rear, int size) {
    /* Sort the front portion ascending */
    for (int i = 0; i < front - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < front - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                float tmp = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = tmp;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
    /* Sort the rear portion ascending */
    int rearStart = size - rear;
    for (int i = 0; i < rear - 1; i++) {
        int swapped = 0;
        for (int j = rearStart; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                float tmp = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = tmp;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
}

/*
 * Purpose:   Sorts only the first half of the array using merge sort,
 *            leaving the second half unchanged.
 * Parameters:
 *   arr  - array of floats
 *   size - total number of elements in the array
 * Example:   float arr[] = {5.0, 3.0, 1.0, 4.0, 2.0};
 *            mergeSortFirstHalf(arr, 5);
 *            // arr is now {1.0, 3.0, 5.0, 4.0, 2.0}
 * Effect:    Modifies arr[0..size/2-1] in-place in ascending order.
 *            Elements in the second half are unchanged.
 * Return:    void
 */
void mergeSortFirstHalf(float arr[], int size) {
    int half = size / 2;
    if (half > 1)
        mergeSortHelper(arr, 0, half - 1);
}

/*
 * Purpose:   Sorts an array using a hybrid merge-insertion sort. Uses
 *            insertion sort for subarrays smaller than THRESHOLD, and
 *            merge sort otherwise, combining the strengths of both.
 * Parameters:
 *   arr   - array of floats to sort
 *   left  - starting index of the subarray
 *   right - ending index of the subarray
 * Example:   float arr[] = {5.0, 3.0, 1.0, 4.0, 2.0};
 *            hybridMergeSort(arr, 0, 4);
 *            // arr is now {1.0, 2.0, 3.0, 4.0, 5.0}
 * Effect:    Modifies arr in-place in ascending order. Uses insertion sort
 *            when subarray size < THRESHOLD (15), merge sort otherwise.
 * Return:    void
 */
void hybridMergeSort(float arr[], int left, int right) {
    if (right - left + 1 < THRESHOLD) {
        for (int i = left + 1; i <= right; i++) {
            float key = arr[i];
            int j = i - 1;
            while (j >= left && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
        return;
    }
    if (left < right) {
        int mid = left + (right - left) / 2;
        hybridMergeSort(arr, left, mid);
        hybridMergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

/*
 * Purpose:   Sorts the subarray arr[left..right] using quicksort with
 *            the middle element as the pivot instead of the last element.
 * Parameters:
 *   arr   - array of floats to sort
 *   left  - starting index of the subarray
 *   right - ending index of the subarray
 * Example:   float arr[] = {5.0, 3.0, 1.0, 4.0, 2.0};
 *            quickSortPivot(arr, 0, 4);
 *            // arr is now {1.0, 2.0, 3.0, 4.0, 5.0}
 * Effect:    Modifies arr in-place in ascending order using the middle
 *            element as pivot, which reduces worst-case scenarios.
 * Return:    void
 */
void quickSortPivot(float arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        float tmp = arr[mid]; arr[mid] = arr[right]; arr[right] = tmp;

        float pivot = arr[right];
        int i = left - 1;
        for (int j = left; j < right; j++) {
            if (arr[j] <= pivot) {
                i++;
                float t = arr[i]; arr[i] = arr[j]; arr[j] = t;
            }
        }
        float t = arr[i + 1]; arr[i + 1] = arr[right]; arr[right] = t;
        int pi = i + 1;

        quickSortPivot(arr, left, pi - 1);
        quickSortPivot(arr, pi + 1, right);
    }
}