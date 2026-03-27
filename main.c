/*
    Name: [Muhammad Shayan]
    Student ID: [1384496]
    Due Date: March 27th, at 11:59pm
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