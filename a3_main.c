#include "a3.h"

void loadArray(const char *filename, float floatArr[], int size) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return;
    }
    
    int index = 0;

    while (index < size && fscanf(file, "%f%*[, \n]", &floatArr[index]) == 1) {
        index++;
    }

    fclose(file);
}

int main(void) {
    float arr[MAX_ARRAY_SIZE];
    char *filename = "data.csv";
    loadArray(filename, arr, MAX_ARRAY_SIZE);

    clock_t start = clock();
    insertionSort(arr, MAX_ARRAY_SIZE);
    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Insertion Sort Execution time: %f seconds\n", time_spent);

    loadArray(filename, arr, MAX_ARRAY_SIZE);

    start = clock();
    bubbleSort(arr, MAX_ARRAY_SIZE);
    end = clock();

    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Bubble Sort Execution time: %f seconds\n", time_spent);

    return 0;
}