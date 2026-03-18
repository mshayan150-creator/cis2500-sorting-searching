#include "a3.h"
#include <string.h>

/* ─────────────────────────────────────────────
   Utility: load CSV into array
   ───────────────────────────────────────────── */
void loadArray(const char *filename, float *arr, int size) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Error: could not open %s\n", filename);
        exit(1);
    }
    int count = 0;
    char line[65536];
    while (fgets(line, sizeof(line), fp) && count < size) {
        char *token = strtok(line, ",\n\r");
        while (token != NULL && count < size) {
            arr[count++] = (float)atof(token);
            token = strtok(NULL, ",\n\r");
        }
    }
    fclose(fp);
}

/* ─────────────────────────────────────────────
   PART 1 — Standard Sorting Algorithms
   ───────────────────────────────────────────── */

/* Selection Sort */
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

/* Insertion Sort */
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

/* Bubble Sort */
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

static void mergeSortHelper(float arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortHelper(arr, left, mid);
        mergeSortHelper(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

/* Merge Sort */
void mergeSort(float arr[], int size) {
    mergeSortHelper(arr, 0, size - 1);
}

/* ── Quick Sort helpers ── */
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

static void quickSortHelper(float arr[], int left, int right) {
    if (left < right) {
        int pi = partition(arr, left, right);
        quickSortHelper(arr, left, pi - 1);
        quickSortHelper(arr, pi + 1, right);
    }
}

/* Quick Sort */
void quickSort(float arr[], int size) {
    quickSortHelper(arr, 0, size - 1);
}

/* ─────────────────────────────────────────────
   PART 2 — Sorting Variants
   ───────────────────────────────────────────── */

/* 1. Selection Sort Range: sort only indices [start, end] */
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

/* 2. Insertion Sort From: sort from startIndex to end of array */
void insertionSortFrom(float arr[], int size, int startIndex) {
    if (startIndex <= 0) startIndex = 1;
    for (int i = startIndex; i < size; i++) {
        float key = arr[i];
        int j = i - 1;
        /* Only shift elements within the [startIndex-1 .. i] window */
        while (j >= startIndex - 1 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

/* 3. Bubble Sort Front and Rear: sort first `front` and last `rear` elements */
void bubbleSortFrontAndRear(float arr[], int front, int rear, int size) {
    /* Sort the front portion */
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
    /* Sort the rear portion */
    int rearStart = size - rear;
    for (int i = rearStart; i < size - 1; i++) {
        int swapped = 0;
        for (int j = rearStart; j < rearStart + (size - i - 1) - (rearStart - 1); j++) {
            if (arr[j] > arr[j + 1]) {
                float tmp = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = tmp;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
}

/* 4. Merge Sort First Half: only sort the first half */
void mergeSortFirstHalf(float arr[], int size) {
    int half = size / 2;
    if (half > 1)
        mergeSortHelper(arr, 0, half - 1);
}

/* 5. Hybrid Merge-Insertion Sort */
void hybridMergeSort(float arr[], int left, int right) {
    if (right - left + 1 < THRESHOLD) {
        /* Use insertion sort on this small subarray */
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

/* 6. Quick Sort with middle element as pivot */
void quickSortPivot(float arr[], int left, int right) {
    if (left < right) {
        /* Move middle element to end to reuse partition logic */
        int mid = left + (right - left) / 2;
        float tmp = arr[mid]; arr[mid] = arr[right]; arr[right] = tmp;

        /* Standard partition with pivot at right */
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