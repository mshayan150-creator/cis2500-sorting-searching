#include "a3.h"

/* ─────────────────────────────────────────────
   PART 3 — Searching Algorithms
   ───────────────────────────────────────────── */

/*
 * Purpose:   Searches for a target value in an unsorted array using
 *            linear search, returning the index of the first match.
 * Parameters:
 *   arr    - array of floats to search
 *   size   - number of elements in the array
 *   target - float value to search for
 * Example:   float arr[] = {3.1, 1.2, 2.5};
 *            linearSearch(arr, 3, 1.2); // returns 1
 *            linearSearch(arr, 3, 9.9); // returns -1
 * Effect:    No modifications to the array.
 * Return:    Index of first occurrence of target, or -1 if not found
 */
int linearSearch(float arr[], int size, float target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target)
            return i;
    }
    return -1;
}

/*
 * Purpose:   Searches for all occurrences of a target value in an array
 *            using linear search, storing every matching index.
 * Parameters:
 *   arr     - array of floats to search
 *   size    - number of elements in the array
 *   target  - float value to search for
 *   indices - array to store the indices of all matches
 * Example:   float arr[] = {1.2, 3.1, 1.2, 2.5};
 *            int idx[4];
 *            linearSearchAll(arr, 4, 1.2, idx); // returns 2, idx={0,2}
 * Effect:    Populates indices[] with all positions where target appears.
 * Return:    Number of times target was found in the array
 */
int linearSearchAll(float arr[], int size, float target, int indices[]) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == target)
            indices[count++] = i;
    }
    return count;
}

/*
 * Purpose:   Searches for a target value in a sorted array using binary
 *            search, returning the index of a matching element.
 * Parameters:
 *   arr    - sorted array of floats to search
 *   size   - number of elements in the array
 *   target - float value to search for
 * Example:   float arr[] = {1.2, 2.5, 3.1};
 *            binarySearch(arr, 3, 2.5); // returns 1
 *            binarySearch(arr, 3, 9.9); // returns -1
 * Effect:    No modifications to the array.
 * Return:    Index of target if found, or -1 if not found
 */
int binarySearch(float arr[], int size, float target) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

/*
 * Purpose:   Searches a sorted array for the first occurrence of a
 *            duplicate value. Returns -1 if the value is not found or
 *            if it is not a duplicate.
 * Parameters:
 *   arr    - sorted array of floats to search
 *   size   - number of elements in the array
 *   target - float value to search for
 * Example:   float arr[] = {1.2, 2.5, 3.4, 3.4, 3.4, 6.8};
 *            binarySearchFirst(arr, 6, 3.4); // returns 2
 *            binarySearchFirst(arr, 6, 2.5); // returns -1 (not duplicate)
 *            binarySearchFirst(arr, 6, 9.9); // returns -1 (not found)
 * Effect:    No modifications to the array.
 * Return:    Index of the first occurrence of target if it is a duplicate,
 *            or -1 otherwise
 */
int binarySearchFirst(float arr[], int size, float target) {
    int left = 0, right = size - 1;
    int result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            result = mid;
            right = mid - 1;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    if (result == -1) return -1;

    int hasNeighbour = (result + 1 < size && arr[result + 1] == target);
    if (!hasNeighbour) return -1;

    return result;
}

/*
 * Purpose:   Searches for a target value in a sorted array using ternary
 *            search, dividing the array into three parts at each step
 *            using two midpoints.
 * Parameters:
 *   arr    - sorted array of floats to search
 *   left   - starting index of the search range
 *   right  - ending index of the search range
 *   target - float value to search for
 * Example:   float arr[] = {1.2, 2.5, 3.4, 6.8, 8.1};
 *            ternarySearch(arr, 0, 4, 3.4); // returns 2
 *            ternarySearch(arr, 0, 4, 9.9); // returns -1
 * Effect:    No modifications to the array.
 * Return:    Index of target if found, or -1 if not found
 */
int ternarySearch(float arr[], int left, int right, float target) {
    if (left > right)
        return -1;

    int mid1 = left + (right - left) / 3;
    int mid2 = right - (right - left) / 3;

    if (arr[mid1] == target) return mid1;
    if (arr[mid2] == target) return mid2;

    if (target < arr[mid1])
        return ternarySearch(arr, left, mid1 - 1, target);
    else if (target > arr[mid2])
        return ternarySearch(arr, mid2 + 1, right, target);
    else
        return ternarySearch(arr, mid1 + 1, mid2 - 1, target);
}