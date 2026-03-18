#ifndef A3_H
#define A3_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define THRESHOLD 15
#define MAX_ARRAY_SIZE 1000

void loadArray(const char *filename, float *arr, int size);

void selectionSort(float arr[], int size);
void insertionSort(float arr[], int size);
void bubbleSort(float arr[], int size);
void mergeSort(float arr[], int size);
void quickSort(float arr[], int size);

void selectionSortRange(float arr[], int start, int end, int size);
void insertionSortFrom(float arr[], int size, int startIndex);
void bubbleSortFrontAndRear(float arr[], int front, int rear, int size);
void mergeSortFirstHalf(float arr[], int size);
void hybridMergeSort(float arr[], int left, int right);
void quickSortPivot(float arr[], int left, int right);

int linearSearch(float arr[], int size, float target);
int linearSearchAll(float arr[], int size, float target, int indices[]);
int binarySearch(float arr[], int size, float target);
int binarySearchFirst(float arr[], int size, float target);
int ternarySearch(float arr[], int left, int right, float target);

#endif