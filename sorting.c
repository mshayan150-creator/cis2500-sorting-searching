#include "a3.h"
#include <string.h>


//Utility: load CSV into array
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

/* 
   PART 1 — Standard Sorting Algorithms
    

/* Selection Sort 
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