/*
Quick Sort

This repository contains an implementation of the Quick Sort algorithm in C.
Algorithm Overview

Quick Sort is a comparison-based sorting algorithm that employs a divide-and-conquer strategy. It works by selecting a pivot element from the array and partitioning the other elements into two sub-arrays, according to whether they are less than or greater than the pivot. The sub-arrays are then recursively sorted. This process continues until the entire array is sorted.

The steps of the Quick Sort algorithm are as follows:

    Select a pivot element from the array.
    Partition the array into two sub-arrays: elements less than the pivot and elements greater than the pivot.
    Recursively apply the Quick Sort algorithm to the sub-arrays.
    Combine the sorted sub-arrays and the pivot to obtain the final sorted array.  
*/
#include <stdio.h>

// Function to swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to partition the array and return the pivot index
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Function to perform the quicksort algorithm
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = partition(arr, low, high);

        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}

// Function to print an array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Driver code
int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array before sorting:\n");
    printArray(arr, n);

    quickSort(arr, 0, n - 1);

    printf("Array after sorting:\n");
    printArray(arr, n);

    return 0;
}
