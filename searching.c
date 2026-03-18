#include "a3.h"

/* ─────────────────────────────────────────────
   PART 3 — Searching Algorithms
   ───────────────────────────────────────────── */

/* 1. Linear Search — returns index of first match, or -1 */
int linearSearch(float arr[], int size, float target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target)
            return i;
    }
    return -1;
}

/* 2. Linear Search All — stores all matching indices, returns count */
int linearSearchAll(float arr[], int size, float target, int indices[]) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == target)
            indices[count++] = i;
    }
    return count;
}

/* 3. Binary Search — array must be sorted; returns index or -1 */
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

/* 4. Binary Search First — returns index of FIRST occurrence of a
      duplicate value, or -1 if the value is not a duplicate (or not found) */
int binarySearchFirst(float arr[], int size, float target) {
    int left = 0, right = size - 1;
    int result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            result = mid;
            right = mid - 1;   /* keep searching left for earlier occurrence */
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    /* Per spec: return -1 if value is not a duplicate */
    if (result == -1)
        return -1;

    /* Check whether there is at least one other occurrence */
    int hasNeighbour = (result + 1 < size && arr[result + 1] == target);
    if (!hasNeighbour)
        return -1;

    return result;
}

/* 5. Ternary Search — array must be sorted; returns index or -1 */
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
